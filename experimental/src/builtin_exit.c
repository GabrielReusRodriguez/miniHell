/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:06:42 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/26 20:04:18 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"
#include "error_handler.h"
#include "libft.h"

static  bool    bultin_exit_is_numeric(t_string arg)
{
	size_t  i;

	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0)
			return false;
		i++;
	}
	return (true);
}

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
	size_t  num_args;
	
	(void)parent;
	(void)shell;
	num_args = ft_lstsize(cmd.args);
	if (num_args > 1)
	{
		error_print("Error: Too many arguments\n");
		return (127);
	}
	node = cmd.args;
	if (node)
	{
		token = (t_token *)node->content;
		if (bultin_exit_is_numeric(token->value))
			exit(ft_atoi(token->value));
		else
			exit(EXIT_SUCCESS);
	}
	exit (EXIT_SUCCESS);
}
