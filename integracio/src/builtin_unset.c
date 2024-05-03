/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:13:48 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/04 00:13:29 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "cmd.h"

void	*builtin_unset(t_minishell *shell, t_cmd cmd)
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
		if (env_remove_var(&shell->cfg.env, var.key) == NULL)
			return (NULL);	
	}
	return (shell);
}