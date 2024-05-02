/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:48:03 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/02 23:56:17 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "builtin.h"
#include "libft.h"

bool    builtin_isbuiltin(t_cmd cmd)
{
	if (cmd.exec == NULL || cmd.exec->value == NULL)
		return (false);
	if (ft_strcmp(cmd.exec->value, BUILTIN_CD) == 0)
		return (true);
	if (ft_strcmp(cmd.exec->value, BUILTIN_ECHO) == 0)
		return (true);
	if (ft_strcmp(cmd.exec->value, BUILTIN_ENV) == 0)
		return (true);
	if (ft_strcmp(cmd.exec->value, BUILTIN_EXIT) == 0)
		return (true);
	if (ft_strcmp(cmd.exec->value, BUILTIN_EXPORT) == 0)
		return (true);
	if (ft_strcmp(cmd.exec->value, BUILTIN_PWD) == 0)
		return (true);
    if (ft_strcmp(cmd.exec->value, BUILTIN_UNSET) == 0)
		return (true);
	return (false);
}

void    builtin_exec(t_minishell *shell, t_cmd cmd)
{
	if (cmd.exec == NULL || cmd.exec->value == NULL)
		return ;
	if (ft_strcmp(cmd.exec->value, BUILTIN_CD) == 0)
		return ;
	if (ft_strcmp(cmd.exec->value, BUILTIN_ECHO) == 0)
		return	;
	if (ft_strcmp(cmd.exec->value, BUILTIN_ENV) == 0)
		builtin_env(shell);
	if (ft_strcmp(cmd.exec->value, BUILTIN_EXIT) == 0)
		builtin_exit(shell);
	if (ft_strcmp(cmd.exec->value, BUILTIN_EXPORT) == 0)
		builtin_export(shell, cmd);
	if (ft_strcmp(cmd.exec->value, BUILTIN_PWD) == 0)
		return (true);
    if (ft_strcmp(cmd.exec->value, BUILTIN_UNSET) == 0)
		builtin_unset(shell, cmd);
}