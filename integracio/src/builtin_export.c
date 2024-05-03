/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:08:45 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/03 23:58:23 by gabriel          ###   ########.fr       */
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

void	*builtin_export(t_minishell *shell, t_cmd cmd)
{
	t_string    param;
	t_list      *node;
	t_var       var;
	t_list		*existing_var;

	var = var_new();
	node = cmd.args;
	if (node == NULL)
	{
		printf("Syntax error\n");
		return (shell);
	}
	param = ((t_token *)node->content)->value;
	if (var_init(param, &var) == NULL)
	{
		printf("Syntax error\n");
        return (shell);       
	}
	existing_var = env_findvar(shell->cfg.env, var.key); 
	if (existing_var != NULL)
	{
		if (env_update_var(existing_var, var) == NULL)
		{
			env_destroy(&shell->cfg.env);
			return (NULL);
		}
	}
	else
	{
		if (env_add_var(&shell->cfg.env, var) == NULL)
		{
			env_destroy(&shell->cfg.env);
			return (NULL);
		}
	}
	return (shell);
}