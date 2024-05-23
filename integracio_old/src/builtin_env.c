/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 21:38:01 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/12 23:35:20 by greus-ro         ###   ########.fr       */
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
