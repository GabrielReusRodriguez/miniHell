/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:00:30 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/04 15:19:16 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "builtin.h"
#include "fcntl.h"
#include <stdio.h>

int	set_heredoc(char *redir)
{
	(void)redir;
	return (0);
}
/*
void	init_fd(t_cmd cmd)
{
	if (cmd.red_in->type == TOKEN_TYPE_RED_HERE_DOC)
		cmd.pipe[0] = set_heredoc(cmd.red_in_origin->value);
	else if (cmd.red_in->type == TOKEN_TYPE_RED_INPUT)
		cmd.pipe[0] = open(cmd.red_in_origin->value, O_RDONLY);
	else
		cmd.pipe[0] = STDIN_FILENO;
	if (cmd.red_out->type == TOKEN_TYPE_RED_TRUNCATE)
		cmd.pipe[1] = open(cmd.red_out_dest->value, O_RDWR | O_CREAT | O_TRUNC,
				0644);
	else if (cmd.red_out->type == TOKEN_TYPE_RED_APPEND)
		cmd.pipe[1] = open(cmd.red_out_dest->value, O_RDWR | O_CREAT | O_APPEND,
				420);
	else
		cmd.pipe[1] = STDOUT_FILENO;
}
*/
int	cmd_run(t_minishell *shell, t_cmd cmd)
{
	int		code;

	code = 0;
	if (cmd_isbuiltin(cmd))
		code = builtin_run(shell, cmd, false);
	return (code);
/*	
	init_fd(cmd);
	cmd.paths = ft_split(get_en_var("PATH", envp), ':');
	close_pipes(cmd);
*/
}

int	cmd_set_run(t_minishell *shell, t_cmd_set cmd_set)
{
	int		code;
	size_t	i;

	code = 0;
	i = 0;
	if (cmd_set.num_cmds == 1 && cmd_isbuiltin(cmd_set.cmds[0]))
		code = builtin_run(shell, cmd_set.cmds[0], true);
	else
	{
		while (i < cmd_set.num_cmds)
		{
			//init_fd(cmd_set.cmds[i]);
			code = cmd_run(shell, cmd_set.cmds[i]);
			i++;
		}
	}
	return (code);
}
