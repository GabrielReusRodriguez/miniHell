/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 23:42:12 by gabriel           #+#    #+#             */
/*   Updated: 2024/06/01 01:09:21 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "var.h"
#include "minishell.h"
#include "tokens.h"

void	builtin_export_minishell_refresh_vars(t_minishell *shell, \
					t_string param)
{
	t_var	*var;

	var = env_get_var(shell->cfg.env, param);
	if (var == NULL)
		return ;
	if (ft_strcmp("OLDPWD", param) == 0)
	{
		var_destroy(shell->cfg.var_oldpwd);
		free (shell->cfg.var_oldpwd);
		shell->cfg.var_oldpwd = var;
	}
	if (ft_strcmp("PATH", param) == 0)
	{
		var_destroy(shell->cfg.var_path);
		free (shell->cfg.var_path);
		shell->cfg.var_path = var;
	}
	if (ft_strcmp("PWD", param) == 0)
	{
		var_destroy(shell->cfg.var_pwd);
		free (shell->cfg.var_pwd);
		shell->cfg.var_pwd = var;
	}
}

static int	builtin_export_1var(t_minishell *shell, t_list *args)
{
	t_string	param;
	t_var		var;
	t_list		*existing_var;

	var = var_new();
	param = ((t_token *)args->content)->value;
	if (var_init(param, &var) == NULL)
	{
		ft_putendl_fd("Syntax error", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	existing_var = env_findvar(shell->cfg.env, var.key);
	if (existing_var != NULL)
	{
		if (env_update_var(existing_var, var) == NULL)
			return (builtin_export_destroy(&var, shell));
	}
	else
	{
		if (env_add_var(&shell->cfg.env, var) == NULL)
			return (builtin_export_destroy(&var, shell));
		builtin_export_minishell_refresh_vars(shell, var.key);
	}
	var_destroy(&var);
	return (EXIT_SUCCESS);
}

int	builtin_export_wargs(t_minishell *shell, t_list *args)
{
	t_string	param;
	t_var		var;
	t_list		*node;
	int			last_status;

	last_status = EXIT_SUCCESS;
	node = args;
	while (node != NULL)
	{
		param = ((t_token *)node->content)->value;
		if (ft_istrchr(param, "=") >= 0)
		{
			var = var_new();
			if (var_init(param, &var) != NULL)
				last_status = builtin_export_1var(shell, node);
			else
			{
				ft_putendl_fd("Syntax error", STDERR_FILENO);
				last_status = EXIT_FAILURE;
			}
			var_destroy(&var);
		}
		node = node->next;
	}
	return (last_status);
}
