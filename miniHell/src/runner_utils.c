/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:47:28 by gabriel           #+#    #+#             */
/*   Updated: 2024/06/06 21:51:59 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"
#include "runner.h"
#include "perm.h"
#include "dir.h"
#include "error_handler.h"

bool	runner_islastcmd(t_run_env run_env)
{
	if (run_env.num_cmd == run_env.total_cmd - 1)
		return (true);
	return (false);
}

/*
	We check if there is only a command and it is a builtin
*/
bool	runner_is_unique_builtin_cmd(t_cmd_set *cmd_set)
{
	if (cmd_set->cmd_count == 1 && cmd_isbuiltin(cmd_set->cmds[0]) == true)
		return (true);
	return (false);
}

/*
https://www.gnu.org/software/bash/manual/html_node/Shell-Builtin-Commands.html
https://unix.stackexchange.com/questions/471221/\
		how-bash-builtins-works-with-pipeline

	We get the full route of the exec cmd.
	First we check if it is a dir,
	Then we check the permissions without path
	finally we check eht epermissions with path.
*/
bool	runner_get_exec(t_cmd *cmd, t_string *paths)
{
	if (is_dir(cmd->exec->value) == true)
	{
		cmd->status = PERM_IS_DIR;
		error_print("Error: Is a directory.\n");
		return (false);
	}
	if (permission_exec_check(cmd) == true)
		return (true);
	else
	{
		if (cmd->status >= 0)
			return (false);
	}
	if (permission_exec_check_with_path(cmd, paths) == true)
		return (true);
	else
		return (false);
}
