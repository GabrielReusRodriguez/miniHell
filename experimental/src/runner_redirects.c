/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:50:21 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/29 09:55:18 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>

#include "datatypes.h"
#include "cmd.h"
#include "redirect.h"
#include "runner.h"
#include "fd.h"
#include "pipes.h"

/*
	Here we prepare the input redirections
	We have to take the last redirect 
*/
bool	runner_treat_inputredir(t_cmd *cmd)
{
	t_list		*node;
	t_redirect	*token;
	int			heredoc_fd[2];
	bool		last_is_heredoc;

	last_is_heredoc = false;
	node = cmd->redir_in;
	while (node != NULL)
	{
		token = ((t_redirect *)node->content);
		fd_close(cmd->fd_input);
		if (token->type->type == TOKEN_TYPE_RED_INPUT)
		{
			cmd->fd_input = open(token->target->value, O_RDONLY);
			if (cmd->fd_input < 0)
			{
				perror("Error");
				cmd->status = EXIT_FAILURE;
				return (false);
			}
			last_is_heredoc = false;
		}
		if (token->type->type == TOKEN_TYPE_RED_HERE_DOC)
			last_is_heredoc = true;
		node = node->next;
	}
	if (last_is_heredoc)
	{
		pipe(heredoc_fd);
		dup2(heredoc_fd[PIPE_READ_FD], STDIN_FILENO);
		ft_putstr_fd(cmd->here_doc, heredoc_fd[PIPE_WRITE_FD]);
		pipes_close_pipe(heredoc_fd);
		cmd->fd_input = -1;
	}
	return (true);
}

/*
	Here we prepare the output redirections
	First we check if there is a output redirect
*/
void	runner_treat_outputredir(t_cmd *cmd, t_run_env run_env)
{
	t_list		*node;
	t_redirect	*redirect;

	node = cmd->redir_out;
	while (node != NULL)
	{
		fd_close(cmd->fd_output);
		redirect = (t_redirect *)node->content;
		if (redirect->type->type == TOKEN_TYPE_RED_TRUNCATE)
		{
			cmd->fd_output = fd_open_file_truncate(redirect->target->value);
			if (cmd->fd_output < 0)
			{
				perror("Error");
				cmd->status = EXIT_FAILURE;
				return ;
			}
		}
		if (redirect->type->type == TOKEN_TYPE_RED_APPEND)
		{
			cmd->fd_output = fd_open_file_append(redirect->target->value);
			if (cmd->fd_output < 0)
			{
				perror("Error");
				cmd->status = EXIT_FAILURE;
				return ;
			}
		}
		node = node->next;
	}
	if (run_env.total_cmd > 1 && runner_islastcmd(run_env) == false)
		pipe(cmd->pipe);
	else
		pipes_init(cmd->pipe);
}
