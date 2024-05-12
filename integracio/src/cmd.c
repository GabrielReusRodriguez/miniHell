/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:45:59 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/12 23:28:19 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "tokens.h"
#include "libft.h"
#include "parser.h"
#include "debug.h"
#include "redirect.h"
#include "error_handler.h"

//TODO: WORK IN PROGRESS.....
t_cmd	cmd_new(void)
{
	t_cmd	cmd;

	cmd.exec = NULL;
	cmd.args = NULL;
	cmd.redir_in = NULL;
	cmd.redir_out = NULL;
	cmd.status = -1;
	return (cmd);
}

void	cmd_destroy(t_cmd *cmd)
{
	if (cmd->exec != NULL)
		token_free(cmd->exec);
	if (cmd->args != NULL)
		ft_lstclear(&cmd->args, token_free_node);
	if (cmd->redir_in != NULL)
		ft_lstclear(&cmd->redir_in, redirect_freenode);
	if (cmd->redir_out != NULL)
		ft_lstclear(&cmd->redir_out, redirect_freenode);
}

void	cmd_destroy_set(t_cmd_set *cmd_set)
{
	size_t	i;

	if (cmd_set->cmds != NULL)
	{
		i = 0;
		while (i < cmd_set->cmd_count)
		{
			cmd_destroy(cmd_set->cmds + i);
			i++;
		}
		free(cmd_set->cmds);
	}
}

t_cmd_set	cmd_create_set(t_token_set token_set)
{
	t_cmd_set	cmd_set;
	size_t		i;

	cmd_set.cmd_count = parser_count_cmds(token_set);
	if (cmd_set.cmd_count == 0)
	{
		cmd_set.cmds = NULL;
		return (cmd_set);
	}
	cmd_set.cmds = (t_cmd *)malloc(cmd_set.cmd_count * sizeof(t_cmd));
	if (cmd_set.cmds == NULL)
	{
		cmd_set.cmd_count = 0;
		cmd_set.cmds = NULL;
		return (cmd_set);
	}
	i = 0;
	while (i < cmd_set.cmd_count)
	{
		cmd_set.cmds[i] = cmd_new();
		i++;
	}
	return (cmd_set);
}
