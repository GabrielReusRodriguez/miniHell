/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:18:22 by abluis-m          #+#    #+#             */
/*   Updated: 2024/06/04 22:54:13 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "builtin.h"
#include "error_handler.h"
#include "perm.h"

int	builtin_run(t_minishell *shell, t_cmd cmd, bool parent)
{
	t_token	*token;

	token = cmd.exec;
	if (ft_strcmp(cmd.exec->value, BUILTIN_CD) == 0)
		return (builtin_cd(shell, cmd));
	if (ft_strcmp(token->value, BUILTIN_ECHO) == 0)
		return (builtin_echo(cmd));
	if (ft_strcmp(cmd.exec->value, BUILTIN_ENV) == 0)
		return (builtin_env(shell));
	if (ft_strcmp(token->value, BUILTIN_EXIT) == 0)
		return (builtin_exit(shell, cmd, parent));
	if (ft_strcmp(cmd.exec->value, BUILTIN_EXPORT) == 0)
		return (builtin_export(shell, cmd));
	if (ft_strcmp(cmd.exec->value, BUILTIN_PWD) == 0)
		return (builtin_pwd(shell, cmd));
	if (ft_strcmp(cmd.exec->value, BUILTIN_UNSET) == 0)
		return (builtin_unset(shell, cmd));
	error_print("Error: Command not found\n");
	return (PERM_NO_COMMAND);
}

bool	cmd_isbuiltin(t_cmd cmd)
{
	t_token	*token;

	token = cmd.exec;
	if (ft_strcmp(token->value, BUILTIN_ECHO) == 0)
		return (true);
	if (ft_strcmp(token->value, BUILTIN_EXIT) == 0)
		return (true);
	if (ft_strcmp(token->value, BUILTIN_CD) == 0)
		return (true);
	if (ft_strcmp(token->value, BUILTIN_PWD) == 0)
		return (true);
	if (ft_strcmp(token->value, BUILTIN_EXPORT) == 0)
		return (true);
	if (ft_strcmp(token->value, BUILTIN_UNSET) == 0)
		return (true);
	if (ft_strcmp(token->value, BUILTIN_ENV) == 0)
		return (true);
	return (false);
}
