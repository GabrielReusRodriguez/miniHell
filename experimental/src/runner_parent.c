/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:56:49 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/29 08:19:18 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "runner.h"
#include "fd.h"
#include "pipes.h"

/*
	The parent process, we only have to do the dup of stdin of the pipe to 
	prepare the reading of stdin (pipe ) of the next proc.
*/
int	runner_parent_process(t_cmd *cmd, t_run_env run_env)
{
	fd_close(cmd->fd_input);
	if (run_env.total_cmd > 1)
	{
		if (runner_islastcmd(run_env) == false)
			dup2(cmd->pipe[PIPE_READ_FD], STDIN_FILENO);
		pipes_close_pipe(cmd->pipe);
	}
	return (0);
}
