/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:45:59 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/24 23:17:28 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "tokens.h"
#include "libft.h"

//TODO: WORK IN PROGRESS.....

t_cmd	cmd_new(void)
{
	t_cmd	cmd;

	cmd.first_token = NULL;
	cmd.last_token = NULL;
	cmd.status = -1;
	return (cmd);
}

void	cmd_destroy(t_cmd *cmd)
{
	ft_lstclear(&cmd->args, token_free);
}

bool	ft_cmd_isvalid(t_cmd cmd)
{
	return (true);
}

void    cmd_destroy_set(t_cmd_set *cmd_set)
{
    size_t  i;

    i = 0;
    while (i< cmd_set->num_cmds)
    {
        cmd_destroy(cmd_set->cmds + i);
        i++;
    }
}