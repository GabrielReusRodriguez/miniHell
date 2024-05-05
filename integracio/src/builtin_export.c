/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:08:45 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/05 18:50:52 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
https://www.computerhope.com/unix/bash/export.htm

On Unix-like operating systems, export is a builtin command of the Bash shell. It designates specified variables and functions to be passed to child processes.

Normally, when you run a command at the bash prompt, a dedicated process is created with its own environment, exclusively for running your command. Any variables and functions you defined before running the command are not shared with new processes — unless you explicitly mark them with export.

Syntax 
export [-f] [-n] [name[=value] ...]

*/

#include <stdio.h>

#include "minishell.h"
#include "cmd.h"

static int	builtin_export_noargs(t_minishell *shell)
{
	t_list	*var_list;
	t_var	*var;
	var_list = shell->cfg.env.vars;
	while (var_list != NULL)
	{
		var = (t_var *)var_list->content;
		printf("declare -x %s=%s\n",var->key ,var->value);
		var_list = var_list->next;
	}
	return (EXIT_SUCCESS);
}

static int builtin_export_wargs(t_minishell *shell, t_list *args)
{
	t_string    param;
	t_var       var;
	t_list		*existing_var;

	var = var_new();
	param = ((t_token *)args->content)->value;
	if (var_init(param, &var) == NULL)
	{
		printf("Syntax error\n");
        return (1);
	}
	existing_var = env_findvar(shell->cfg.env, var.key); 
	if (existing_var != NULL)
	{
		if (env_update_var(existing_var, var) == NULL)
		{
            var_destroy(&var);
			env_destroy(&shell->cfg.env);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if (env_add_var(&shell->cfg.env, var) == NULL)
		{
            var_destroy(&var);
			env_destroy(&shell->cfg.env);
			return (EXIT_FAILURE);
		}
	}
    var_destroy(&var);
	return (EXIT_SUCCESS);
}

int	builtin_export(t_minishell *shell, t_cmd cmd)
{
	t_list      *node;

	node = cmd.args;
	if (node == NULL)
		return (builtin_export_noargs(shell));
	return (builtin_export_wargs(shell, node));
}
