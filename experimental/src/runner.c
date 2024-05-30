/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:35:29 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/31 01:23:32 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>

#include "minishell.h"
#include "cmd.h"
#include "signal_handler.h"
#include "ptr.h"
#include "builtin.h"
#include "error_handler.h"
#include "runner.h"
#include "fd.h"
#include "pipes.h"

/*
	YASFTAN
	Yet Another Stupid Function To Avoid Norminette
*/
static int	runner_config_redirs(t_minishell *shell, t_cmd_set *cmd_set, \
				t_cmd *cmd, t_run_env run_env)
{
	if (runner_treat_inputredir(cmd) == true)
		runner_treat_outputredir(cmd, run_env);
	if (runner_is_unique_builtin_cmd(cmd_set) == true)
	{
		if (cmd->status >= 0)
		{
			shell->status.return_status = cmd->status;
			return (shell->status.return_status);
		}
		if (cmd->fd_output > 0)
			pipes_dup2(cmd->fd_output, STDOUT_FILENO);
		fd_close(cmd->fd_output);
		shell->status.return_status = builtin_run(shell, \
			cmd_set->cmds[0], true);
		return (shell->status.return_status);
	}
	return (-1);
}

/*
	HEre we run the command. we have to prepare redirections of input
	and output before fork.
*/
int	runner_run_cmd(t_minishell *shell, t_cmd_set *cmd_set, t_run_env run_env)
{
	pid_t		pid;
	t_cmd		*cmd;
	int			result;

	cmd = &cmd_set->cmds[run_env.num_cmd];
	result = runner_config_redirs(shell, cmd_set, cmd, run_env);
	if (result >= 0)
		return (shell->status.return_status);
	pid = fork();
	if (pid != 0)
	{
		if (pid < 0)
		{
			error_print("Error at fork.\n");
			return (FORK_ERROR);
		}
		signal_set_mode(SIGNAL_MODE_NOOP);
		runner_parent_process(cmd, run_env);
	}
	else
	{
		signal_set_mode(SIGNAL_MODE_DEFAULT);
		runner_child_process(shell, cmd, run_env);
	}
	return (EXIT_SUCCESS);
}

/*
in ash, zsh, pdksh, bash, the Bourne shell, $? is 128 + n. What that means is 
	that in those shells, if you get a $? of 129, you don't know whether it's 
	because the process exited with exit(129) or whether it was killed by the 
	signal 1 (HUP on most systems). But the rationale is that shells, when they
	do exit themselves, by default return the exit status of the last exited 
	command. By making sure $? is never greater than 255, that allows to have 
	a consistent exit status:

https://unix.stackexchange.com/questions/99112/default-exit-code-when-process\
	-is-terminated
*/
static int	runner_determine_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFSTOPPED(status))
		return (128 + WSTOPSIG(status));
	return (status);
}

/*
	Nos quedamos con el status del mayor pid ya que el pid
	es positivo e incremental.
*/
void	runner_get_status(t_minishell *shell, t_cmd_set *cmd_set)
{
	pid_t	pid;
	pid_t	greater_pid;
	size_t	i;
	int		status;

	if (shell->status.return_status >= 0)
		return ;
	greater_pid = 0;
	i = 0;
	while (i < cmd_set->cmd_count)
	{
		pid = wait(&status);
		if (pid > greater_pid)
		{
			shell->status.return_status = status;
			greater_pid = pid;
		}
		i++;
	}
	shell->status.return_status = runner_determine_status(\
			shell->status.return_status);
}

/*
https://stackoverflow.com/questions/53924800/how-to-recover-stdin-overwritten-\
	by-dup2

If we start to do dup2 we loose the original stdin, so we have to save and when
we finish, we do the reverse dup2IN
We do not save the original stdout because we do the dup2 at children process 
of fork and when process exit it closes automaticaly
*/
int	runner_run_cmd_set(t_minishell *shell, t_cmd_set *cmd_set)
{
	size_t		i;
	t_run_env	run_env;

	shell->status.return_status = -1;
	run_env.paths = minishell_path_2_vector(*shell);
	run_env.envp = env_to_vector(shell->cfg.env);
	run_env.total_cmd = cmd_set->cmd_count;
	i = 0;
	cmd_set->old_stdin = pipes_dup(STDIN_FILENO);
	cmd_set->old_stdout = pipes_dup(STDOUT_FILENO);
	while (i < cmd_set->cmd_count)
	{
		run_env.num_cmd = i;
		runner_run_cmd(shell, cmd_set, run_env);
		i++;
	}
	pipes_dup2(cmd_set->old_stdin, STDIN_FILENO);
	pipes_dup2(cmd_set->old_stdout, STDOUT_FILENO);
	fd_close(cmd_set->old_stdin);
	fd_close(cmd_set->old_stdout);
	ptr_freematrix(run_env.envp);
	ptr_freematrix(run_env.paths);
	runner_get_status(shell, cmd_set);
	return (shell->status.return_status);
}
