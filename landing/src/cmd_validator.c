/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:26:03 by gabriel           #+#    #+#             */
/*   Updated: 2024/04/30 20:16:55 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"
#include "cmd.h"
#include "error_handler.h"

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

bool	cmd_validate_set(t_cmd_set cmd_set)
{
	size_t	i;

	i = 0;
	while (i < cmd_set.num_cmds)
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
