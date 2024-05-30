/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permission_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 21:33:36 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/31 01:22:42 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>

#include "datatypes.h"
#include "cmd.h"
#include "perm.h"
#include "error_handler.h"
#include "ptr.h"

bool	permission_exec_check(t_cmd *cmd)
{
	if (access(cmd->exec->value, F_OK) == 0)
	{
		if (access(cmd->exec->value, X_OK) == 0)
			return (true);
		else
		{
			perror("Error");
			cmd->status = PERM_NO_EXEC;
			return (false);
		}
	}
	return (false);
}

static void	permission_exec_set_out_status(t_cmd *cmd, bool file_found)
{
	if (file_found)
	{
		error_print("Error: Permission denied\n");
		cmd->status = PERM_NO_EXEC;
	}
	else
	{
		error_print("Error: Command not found\n");
		cmd->status = PERM_NO_COMMAND;
	}
}

bool	permission_exec_check_with_path(t_cmd *cmd, t_string *paths)
{
	size_t		i;
	t_string	exec;
	bool		file_found;

	i = 0;
	file_found = false;
	while (paths[i] != NULL)
	{
		exec = ft_strjoin(paths[i], cmd->exec->value);
		ptr_check_malloc_return(exec, "Error at memory malloc.\n");
		if (access(exec, F_OK) == 0)
		{
			file_found = true;
			if (access(exec, X_OK) == 0)
			{
				free (cmd->exec->value);
				cmd->exec->value = exec;
				return (true);
			}
		}
		free (exec);
		i++;
	}
	permission_exec_set_out_status(cmd, file_found);
	return (false);
}
