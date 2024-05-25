/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 21:35:29 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/25 02:19:44 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "minishell.h"
#include "cmd.h"
#include "signal_handler.h"
#include "environment.h"
#include "ptr.h"
#include "builtin.h"


//https://www.gnu.org/software/bash/manual/html_node/Shell-Builtin-Commands.html
//https://unix.stackexchange.com/questions/471221/how-bash-builtins-works-with-pipeline

void	runner_get_exec(t_cmd *cmd, t_string *paths)
{
	size_t      i;
	t_string	exec;
	
	i = 0;
	while (paths[i] != NULL)
	{
		exec = ft_strjoin(paths[i], cmd->exec->value);
		ptr_check_malloc_return(exec, "Error at memory malloc.\n");
		if (access(exec, X_OK) == 0)
		{
			free (cmd->exec->value);
			cmd->exec->value = exec;
			return ;
		}
		free (exec);
		i++;
	}
}

void	runner_treat_inputredir(t_cmd cmd)
{
	(void)cmd;
}

void	runner_treat_outputredir(t_cmd cmd)
{
	(void)cmd;
}

#include <stdio.h>

int	runner_run_cmd(t_minishell *shell, t_cmd *cmd,t_string *paths, t_string *envp)
{
	pid_t pid;
	t_string	*argv;

	if (cmd_isbuiltin(*cmd) == false)
		runner_get_exec(cmd, paths);
	runner_treat_inputredir(*cmd);
	runner_treat_outputredir(*cmd);
	pid = fork();
	if (pid != 0)
	{
		if (pid < 0)
			return (EXIT_FAILURE);
		//Parent process
		signal_set_mode(SIGNAL_MODE_NOOP);
	}
	else
	{
		//child process
		signal_set_mode(SIGNAL_MODE_DEFAULT);
		if (cmd_isbuiltin(*cmd) == true)
			exit(builtin_run(shell, *cmd, true));
		else
		{
			argv = cmd_join_exec_and_args(*cmd);
			if (execve(cmd->exec->value, argv, envp) < 0)
			{
				//shell->status.return_status = EXIT_FAILURE;
				ptr_freematrix(argv);
				exit (EXIT_FAILURE);
			}
		}
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

int runner_run_cmd_set(t_minishell *shell, t_cmd_set *cmd_set)
{
	size_t	    i;
	t_string    *paths;
	t_string    *envp;

	if (runner_is_unique_builtin_cmd(cmd_set) == true)
	{
		return (builtin_run(shell, cmd_set->cmds[0], true));
	}
	paths = minishell_path_2_vector(*shell);
	envp = env_to_vector(shell->cfg.env);
	i = 0;
	while (i < cmd_set->cmd_count)
	{
		runner_run_cmd(shell, &cmd_set->cmds[i], paths, envp);
		i++;
	}
	ptr_freematrix(envp);
	ptr_freematrix(paths);
	runner_get_status(shell, cmd_set);
	return (shell->status.return_status);
}
