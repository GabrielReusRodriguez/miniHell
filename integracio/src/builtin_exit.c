/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:06:42 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/26 12:16:53 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"
#include <stdio.h>

bool	check_all_digits(t_string str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_too_many_args(t_list *node)
{
	if (node->next == NULL)
		return (false);
	else
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (true);
	}
}

int	builtin_exit(t_minishell *shell, t_cmd cmd, bool parent)
{
	t_list	*node;
	t_token	*token;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	node = cmd.args;
	if (node)
	{
		token = (t_token *)node->content;
		if (check_all_digits(token->value))
		{
			shell->status.return_status = ft_atoi(token->value);
			if (check_too_many_args (node))
				shell->status.return_status = EXIT_FAILURE;
		}
		else
			shell->status.return_status = EXIT_FAILURE;
	}
	else
		shell->status.return_status = EXIT_SUCCESS;
	if (parent)
		shell->status.run = false;
	else
		exit(shell->status.return_status);
	return (shell->status.return_status);
}
