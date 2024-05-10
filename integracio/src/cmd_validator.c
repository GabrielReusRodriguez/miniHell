/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:26:03 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/10 12:49:39 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"
#include "cmd.h"
#include "error_handler.h"
#include "redirect.h"

bool	cmd_isvalid(t_cmd cmd)
{
	t_redirect	*redir;

	while(cmd.redir_in != NULL)
	{
		redir = (t_redirect *)cmd.redir_in->content;
		if (redir == NULL || redir->type == NULL || redir->target == NULL)
			return (false);
		cmd.redir_in = cmd.redir_in->next;
	}
	while(cmd.redir_out != NULL)
	{
		redir = (t_redirect *)cmd.redir_out->content;
		if (redir == NULL || redir->type == NULL || redir->target == NULL)
			return (false);
		cmd.redir_out = cmd.redir_out->next;
	}
	if (cmd.exec == NULL)
		return (false);
	return (true);
}
