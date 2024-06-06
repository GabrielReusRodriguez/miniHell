/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:35:29 by gabriel           #+#    #+#             */
/*   Updated: 2024/06/06 21:52:28 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		shell->status.return_status = builtin_run(shell, cmd_set->cmds[0], \
										true);
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
	t_cmd		*cmd;
	int			result;

	cmd = &cmd_set->cmds[run_env.num_cmd];
	result = runner_config_redirs(shell, cmd_set, cmd, run_env);
	if (result >= 0)
		return (shell->status.return_status);
	cmd->pid = fork();
	if (cmd->pid != 0)
	{
		if (cmd->pid < 0)
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
	YASFTAN
	Yet Another Stupid Function To Avoid Norminette.
*/
static int	runner_exit_on_stdin_error(t_minishell *shell, t_cmd_set *cmd_set, \
				t_run_env run_env)
{
	size_t	i;

	i = 0;
	while (i < cmd_set->cmd_count)
	{
		fd_close(cmd_set->cmds[i].fd_input);
		fd_close(cmd_set->cmds[i].fd_output);
		i++;
	}
	ptr_freematrix(run_env.envp);
	ptr_freematrix(run_env.paths);
	pipes_dup2(shell->cfg.old_stdin, STDIN_FILENO);
	shell->status.return_status = 130;
	return (shell->status.return_status);
}

/*
https://stackoverflow.com/questions/53924800/how-to-recover-stdin-overwritten-\
	by-dup2

If we start to do dup2 we loose the original stdin, so we have to save and when
we finish, we do the reverse dup2IN
We do not save the original stdout because we do the dup2 at children process 
of fork and when process exit it closes automaticaly

In "if (isatty(STDIN_FILENO) == 0)" we check if stdin is closed because
in heredoc, if we receive an control +C , the signal handler closes the stdin 
and sets to -1 . So we check this condition here.

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
	if (isatty(STDIN_FILENO) == 0)
		return (runner_exit_on_stdin_error(shell, cmd_set, run_env));
	while (i < cmd_set->cmd_count)
	{
		run_env.num_cmd = i;
		runner_run_cmd(shell, cmd_set, run_env);
		i++;
	}
	pipes_dup2(shell->cfg.old_stdin, STDIN_FILENO);
	pipes_dup2(shell->cfg.old_stdout, STDOUT_FILENO);
	ptr_freematrix(run_env.envp);
	ptr_freematrix(run_env.paths);
	runner_get_status(shell, cmd_set);
	return (shell->status.return_status);
}
