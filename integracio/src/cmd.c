/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:45:59 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/24 21:47:31 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cmd.h"
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
