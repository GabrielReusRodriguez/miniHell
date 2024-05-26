/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:08:45 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/25 16:12:38 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
https://www.computerhope.com/unix/bash/export.htm

On Unix-like operating systems, export is a builtin command of the Bash shell. 
It designates specified variables and functions to be passed to child 
processes.

Normally, when you run a command at the bash prompt, a dedicated process is 
created with its own environment, exclusively for running your command. 
Any variables and functions you defined before running the command 
are not shared  with new processes — unless you explicitly mark them with 
export.

Syntax 
export [-f] [-n] [name[=value] ...]

*/

#include <stdio.h>

#include "minishell.h"
#include "environment.h"
#include "cmd.h"
#include "libft.h"

static	void	builtin_export_minishell_refresh_vars(t_minishell *shell, \
					t_string param)
{
	t_var	*var;

	var = env_get_var(shell->cfg.env, param);
	if (var != NULL)
		return ;
	if (ft_strcmp("OLDPWD", param) == 0)
	{
		var_destroy(shell->cfg.var_oldpwd);
		free (shell->cfg.var_oldpwd);
		shell->cfg.var_oldpwd = var;
	}
	if (ft_strcmp("PATH", param) == 0)
	{
		var_destroy(shell->cfg.var_oldpwd);
		free (shell->cfg.var_oldpwd);
		shell->cfg.var_path = var;
	}
	if (ft_strcmp("PWD", param) == 0)
	{
		var_destroy(shell->cfg.var_oldpwd);
		free (shell->cfg.var_oldpwd);
		shell->cfg.var_pwd = var;
	}
}

static int	builtin_export_noargs(t_minishell *shell)
{
	t_list	*var_list;
	t_var	*var;

	var_list = shell->cfg.env.vars;
	while (var_list != NULL)
	{
		var = (t_var *)var_list->content;
		printf("declare -x %s=%s\n", var->key, var->value);
		var_list = var_list->next;
	}
	return (EXIT_SUCCESS);
}

static int	builtin_export_destroy(t_var *var, t_minishell *shell)
{
	var_destroy(var);
	env_destroy(&shell->cfg.env);
	return (EXIT_FAILURE);
}

static int	builtin_export_wargs(t_minishell *shell, t_list *args)
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
	}
	builtin_export_minishell_refresh_vars(shell, var.key);
	var_destroy(&var);
	return (EXIT_SUCCESS);
}

int	builtin_export(t_minishell *shell, t_cmd cmd)
{
	t_list	*node;

	node = cmd.args;
	if (node == NULL)
		return (builtin_export_noargs(shell));
	return (builtin_export_wargs(shell, node));
}
