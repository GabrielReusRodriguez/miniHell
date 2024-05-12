/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:13:48 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/12 23:29:09 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "cmd.h"

int	builtin_unset(t_minishell *shell, t_cmd cmd)
{
	t_string	param;
	t_list		*node;
	t_list		*existing_var;

	node = cmd.args;
	if (node == NULL)
	{
		printf("Syntax error\n");
		return (EXIT_SUCCESS);
	}
	param = ((t_token *)node->content)->value;
	existing_var = env_findvar(shell->cfg.env, param);
	if (existing_var != NULL)
	{
		if (env_remove_var(&shell->cfg.env, param) == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
