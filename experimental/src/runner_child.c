/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:56:29 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/31 21:14:52 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "minishell.h"
#include "cmd.h"
#include "runner.h"
#include "fd.h"
#include "pipes.h"
#include "ptr.h"
#include "error_handler.h"
#include "builtin.h"

/*
	Yet Another Stupid Function To Avoid Norminette
	YASFTAN
*/
static void	runner_child_check_init_status(t_cmd *cmd, t_run_env run_env)
{
	if (cmd->status > 0)
		exit(cmd->status);
	if (cmd->fd_input > 0)
		pipes_dup2(cmd->fd_input, STDIN_FILENO);
	if (cmd->fd_output > 0)
		pipes_dup2(cmd->fd_output, STDOUT_FILENO);
	else
	{
		if (run_env.total_cmd > 1)
		{
			if (runner_islastcmd(run_env) == false)
				pipes_dup2(cmd->pipe[PIPE_WRITE_FD], STDOUT_FILENO);
		}
	}
}

/*
	The child process.
	we run do the dup of stdout to write at the entry of pipe.
	then we get the route and execute 
*/
void	runner_child_process(t_minishell *shell, t_cmd *cmd, t_run_env run_env)
{
	t_string	*argv;

	runner_child_check_init_status(cmd, run_env);
	fd_close(cmd->fd_output);
	fd_close(cmd->fd_input);
	pipes_close_pipe(cmd->pipe);
	if (cmd_isbuiltin(*cmd) == true)
		exit(builtin_run(shell, *cmd, true));
	else
	{
		if (runner_get_exec(cmd, run_env.paths) == false)
			exit (cmd->status);
		argv = cmd_join_exec_and_args(*cmd);
		if (execve(cmd->exec->value, argv, run_env.envp) < 0)
		{
			perror ("Error");
			ptr_freematrix(argv);
			exit (EXIT_FAILURE);
		}
	}
}
