/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:23:45 by gabriel           #+#    #+#             */
/*   Updated: 2024/04/21 23:27:42 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cmd.h"
#include "ft_tokens.h"
#include "libft.h"

t_cmd	ft_cmd_new(void)
{
	t_cmd cmd;

//	cmd.cmd = NULL;
	cmd.first_token = NULL;
	cmd.last_token = NULL;
	cmd.status = -1;
	return (cmd);
}

void	ft_cmd_destroy(t_cmd *cmd)
{
    ft_lstclear(&cmd->args, ft_token_free);
//	free (cmd->cmd);
}

t_bool  ft_cmd_isvalid(t_cmd cmd)
{
//	if ( cmd.cmd == NULL || cmd.first_token == NULL || cmd.last_token == NULL)
//		return (TRUE);
	return (FALSE);
}

