/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:06:42 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/29 07:54:50 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"
#include "error_handler.h"
#include "libft.h"

static bool	bultin_exit_is_numeric(t_string arg)
{
	size_t	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

int	builtin_exit(t_minishell *shell, t_cmd cmd, bool parent)
{
	t_list	*node;
	t_token	*token;
	size_t	num_args;

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
