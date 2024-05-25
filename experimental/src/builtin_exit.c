/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:06:42 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/25 01:45:32 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"
#include <stdio.h>

int	builtin_exit(t_minishell *shell, t_cmd cmd, bool parent)
{
    /*
	t_list	*node;
	t_token	*token;

	node = cmd.args;
	if (node)
	{
		token = (t_token *)node->content;
		shell->status.return_status = ft_atoi(token->value);
	}
	else
		shell->status.return_status = EXIT_SUCCESS;
	if (parent)
		shell->status.run = false;
	return (shell->status.return_status);
    */

    t_list	*node;
	t_token	*token;

   (void)parent;
   (void)shell;
	node = cmd.args;
	if (node)
	{
		token = (t_token *)node->content;
		exit(ft_atoi(token->value));
	}
    exit (EXIT_SUCCESS);
}
