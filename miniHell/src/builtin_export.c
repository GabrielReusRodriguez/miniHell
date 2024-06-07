/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:08:45 by gabriel           #+#    #+#             */
/*   Updated: 2024/06/08 01:05:16 by gabriel          ###   ########.fr       */
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

#include "builtin.h"
#include "minishell.h"
#include "environment.h"
#include "cmd.h"
#include "libft.h"

int	builtin_export_noargs(t_minishell *shell)
{
	t_list	*var_list;
	t_var	*var;

	var_list = shell->cfg.env.vars;
	while (var_list != NULL)
	{
		var = (t_var *)var_list->content;
		printf("declare -x %s=\"%s\"\n", var->key, var->value);
		var_list = var_list->next;
	}
	return (EXIT_SUCCESS);
}

int	builtin_export_destroy(t_var *var, t_minishell *shell)
{
	var_destroy(var);
	env_destroy(&shell->cfg.env);
	return (EXIT_FAILURE);
}

int	builtin_export(t_minishell *shell, t_cmd cmd)
{
	t_list	*node;

	node = cmd.args;
	if (node == NULL)
		return (builtin_export_noargs(shell));
	return (builtin_export_wargs(shell, node));
}
