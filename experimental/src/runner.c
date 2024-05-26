/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:35:29 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/26 23:54:49 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "minishell.h"
#include "cmd.h"
#include "signal_handler.h"
#include "environment.h"
#include "ptr.h"
#include "builtin.h"
#include "error_handler.h"
#include "runner.h"


void    pipe_close_fd(int pipe)
{
	if (pipe >= 0)
		close (pipe);
}

void	pipe_close_pipe(int pipe[2])
{
	pipe_close_fd(pipe[0]);
	pipe_close_fd(pipe[1]);
}

bool	runner_islastcmd(t_run_env run_env)
{
	if (run_env.num_cmd == run_env.total_cmd - 1)
		return (true);
	return (false);
}


//https://www.gnu.org/software/bash/manual/html_node/Shell-Builtin-Commands.html
//https://unix.stackexchange.com/questions/471221/how-bash-builtins-works-with-pipeline

bool	runner_get_exec(t_cmd *cmd, t_string *paths)
{
	size_t      i;
	t_string	exec;

	if (access(cmd->exec->value, X_OK) == 0)
		return (true);
	i = 0;
	while (paths[i] != NULL)
	{
		exec = ft_strjoin(paths[i], cmd->exec->value);
		ptr_check_malloc_return(exec, "Error at memory malloc.\n");
		if (access(exec, X_OK) == 0)
		{
			free (cmd->exec->value);
			cmd->exec->value = exec;
			return (true);
		}
		free (exec);
		i++;
	}
	return (false);
}

void	runner_treat_inputredir(t_cmd *cmd)
{
	(void)cmd;
}

void	runner_treat_outputredir(t_cmd *cmd, t_run_env run_env)
{
	if (run_env.total_cmd > 1 && runner_islastcmd(run_env) == false)
	{
		pipe(cmd->pipe);
	}
	else
	{
		cmd->pipe[PIPE_READ_FD] = -1;
		cmd->pipe[PIPE_WRITE_FD] = -1;
	}
}

void	runner_child_process(t_minishell *shell, t_cmd *cmd, t_run_env run_env)
{
	t_string	*argv;

	if (run_env.total_cmd > 1)
	{
		if (runner_islastcmd(run_env) == false)
			dup2(cmd->pipe[PIPE_WRITE_FD], STDOUT_FILENO);

		pipe_close_pipe(cmd->pipe);
	}
	if (cmd_isbuiltin(*cmd) == true)
		exit(builtin_run(shell, *cmd, true));
	else
	{
		if (runner_get_exec(cmd, run_env.paths) == false)
		{
			error_print("Error: Command not found\n");
			exit(127);
		}
		argv = cmd_join_exec_and_args(*cmd);
		if (execve(cmd->exec->value, argv, run_env.envp) < 0)
		{
			perror ("Error");
			ptr_freematrix(argv);
			exit (EXIT_FAILURE);
		}
	}	
}

int	runner_parent_process(t_cmd *cmd, t_run_env run_env)
{
	//Parent process
	if (run_env.total_cmd > 1)
	{
		if (runner_islastcmd(run_env) == false)
			dup2(cmd->pipe[PIPE_READ_FD], STDIN_FILENO);
		pipe_close_pipe(cmd->pipe);
	}
	return (0);	
}

int	runner_run_cmd(t_minishell *shell, t_cmd_set *cmd_set, t_run_env run_env)
{
	pid_t       pid;
	t_cmd		*cmd;

	cmd = &cmd_set->cmds[run_env.num_cmd];

	runner_treat_inputredir(cmd);
	runner_treat_outputredir(cmd, run_env);
	pid = fork();
	if (pid != 0)
	{
		if (pid < 0)
			return (EXIT_FAILURE);
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
in ash, zsh, pdksh, bash, the Bourne shell, $? is 128 + n. What that means is that in those shells, if you get a $? of 129, you don't know whether it's because the process exited with exit(129) or whether it was killed by the signal 1 (HUP on most systems). But the rationale is that shells, when they do exit themselves, by default return the exit status of the last exited command. By making sure $? is never greater than 255, that allows to have a consistent exit status:
*/
//https://unix.stackexchange.com/questions/99112/default-exit-code-when-process-is-terminated
static int runner_determine_status(int status)
{
	if  (WIFEXITED(status))
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
void	runner_get_status(t_minishell *shell,t_cmd_set *cmd_set)
{
	pid_t	pid;
	pid_t	greater_pid;
	size_t	i;
	int		status;
	
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
	shell->status.return_status = runner_determine_status(shell->status.return_status);
}

bool runner_is_unique_builtin_cmd(t_cmd_set *cmd_set)
{
	if (cmd_set->cmd_count == 1 && cmd_isbuiltin(cmd_set->cmds[0]) == true)
		return (true);
	return (false);
}

/*
https://stackoverflow.com/questions/53924800/how-to-recover-stdin-overwritten-by-dup2

If we start to do dup2 we loose the original stdin, so we have to save and when we finish, we do the reverse dup2
*/
int runner_run_cmd_set(t_minishell *shell, t_cmd_set *cmd_set)
{
	size_t	    i;
	t_run_env	run_env;

	if (runner_is_unique_builtin_cmd(cmd_set) == true)
	{
		return (builtin_run(shell, cmd_set->cmds[0], true));
	}
	run_env.paths = minishell_path_2_vector(*shell);
	run_env.envp = env_to_vector(shell->cfg.env);
	run_env.total_cmd = cmd_set->cmd_count;
	i = 0;
	cmd_set->old_stdin = dup(STDIN_FILENO);
	while (i < cmd_set->cmd_count)
	{
		run_env.num_cmd = i;
//		runner_run_cmd(shell, &cmd_set->cmds[i], run_env);
		runner_run_cmd(shell, cmd_set, run_env);
		i++;
	}
	dup2(cmd_set->old_stdin, STDIN_FILENO);
	close(cmd_set->old_stdin);
	ptr_freematrix(run_env.envp);
	ptr_freematrix(run_env.paths);
	runner_get_status(shell, cmd_set);
	return (shell->status.return_status);
}
