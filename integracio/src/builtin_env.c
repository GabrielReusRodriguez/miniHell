/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:38:01 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/02 21:43:18 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

int	builtin_env(t_minishell *shell)
{
	t_list	*node;
	t_var	*var;

	node = shell->cfg.env.vars;
	while (node != NULL)
	{
		var = (t_var *)node->content;
		printf("%s=%s\n", var->key, var->value);
		node = node->next;	
	}
	return (EXIT_SUCCESS);
}