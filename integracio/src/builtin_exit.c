/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:06:42 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/23 18:42:35 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"
#include <stdio.h>

int	builtin_exit(t_minishell *shell, t_cmd cmd, bool parent)
{
	t_list	*node;
	t_token	*token;

	node = cmd.args;
	// bash: exit: too many arguments
	// bash: exit: 42barcelona: numeric argument required
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
}
