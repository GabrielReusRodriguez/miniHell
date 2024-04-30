/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:45:59 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/30 20:17:30 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "tokens.h"
#include "libft.h"
#include "parser.h"
#include "debug.h"

//TODO: WORK IN PROGRESS.....
t_cmd	cmd_new(void)
{
	t_cmd	cmd;

	cmd.red_in = NULL;
	cmd.red_in_origin = NULL;
	cmd.exec = NULL;
	cmd.args = NULL;
	cmd.red_out = NULL;
	cmd.red_out_dest = NULL;
	cmd.status = -1;
	return (cmd);
}

void	cmd_destroy(t_cmd *cmd)
{
	if (cmd->args != NULL)
		ft_lstclear(&cmd->args, token_free_node);
}

bool	cmd_isvalid(t_cmd cmd)
{
	(void)cmd;
	return (true);
}

void	cmd_destroy_set(t_cmd_set *cmd_set)
{
	size_t	i;

	if (cmd_set->cmds != NULL)
	{
		i = 0;
		while (i < cmd_set->num_cmds)
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

	cmd_set.num_cmds = parser_count_cmds(token_set);
	if (cmd_set.num_cmds == 0)
	{
		cmd_set.cmds = NULL;
		return (cmd_set);
	}
	cmd_set.cmds = (t_cmd *)malloc(cmd_set.num_cmds * sizeof(t_cmd));
	if (cmd_set.cmds == NULL)
	{
		cmd_set.num_cmds = 0;
		cmd_set.cmds = NULL;
		return (cmd_set);
	}
	return (cmd_set);
}
