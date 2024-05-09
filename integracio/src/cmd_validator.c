/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:26:03 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/10 01:22:53 by gabriel          ###   ########.fr       */
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

/*
static bool	cmd_validate(t_cmd cmd)
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
}*/
/*
static bool	cmd_validate(t_cmd cmd)
{
	if (cmd.red_in != NULL && cmd.red_in_origin == NULL)
		return (false);
	if (cmd.red_out != NULL && cmd.red_out_dest == NULL)
		return (false);
	if (cmd.exec == NULL)
		return (false);
	return (true);
}
*/
/*
bool	cmd_validate_set(t_cmd_set cmd_set)
{
	size_t	i;

	i = 0;
	while (i < cmd_set.cmd_count)
	{
		cmd_debug(cmd_set.cmds[i]);
		if (cmd_validate(cmd_set.cmds[i]) == false)
		{
			error_print("Syntax error \n");
			return (false);
		}
		i++;
	}
	return (true);
}
*/