/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:47:28 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/29 08:09:52 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"
#include "runner.h"
#include "ptr.h"

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
*/
bool	runner_get_exec(t_cmd *cmd, t_string *paths)
{
	size_t		i;
	t_string	exec;

	if (access(cmd->exec->value, X_OK) == 0)
		return (true);
	i = 0;
	while (paths[i] != NULL)
	{
		exec = ft_strjoin(paths[i], cmd->exec->value);
		ptr_check_malloc_return(exec, "Error at memory malloc.\n");
		if (access(exec, X_OK) == 0)
		{
			free (cmd->exec->value);
			cmd->exec->value = exec;
			return (true);
		}
		free (exec);
		i++;
	}
	return (false);
}
