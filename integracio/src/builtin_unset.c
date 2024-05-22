/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:13:48 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/22 20:57:52 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "cmd.h"
#include "libft.h"

int	builtin_unset(t_minishell *shell, t_cmd cmd)
{
	t_string	param;
	t_list		*node;
	t_list		*existing_var;

	node = cmd.args;
	if (node == NULL)
	{
		ft_putendl_fd("Syntax error", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	param = ((t_token *)node->content)->value;
	existing_var = env_findvar(shell->cfg.env, param);
	if (existing_var != NULL)
	{
		if (env_remove_var(&shell->cfg.env, param) == NULL)
			return (EXIT_FAILURE);
		if(ft_strcmp("PWD", param) == 0)
			shell->cfg.var_pwd = NULL;
		if(ft_strcmp("OLDPWD", param) == 0)
			shell->cfg.var_oldpwd= NULL;
		if(ft_strcmp("PATH", param) == 0)
			shell->cfg.var_oldpwd= NULL;
	}
	return (EXIT_SUCCESS);
}
