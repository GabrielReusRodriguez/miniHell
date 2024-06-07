/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:06:42 by greus-ro          #+#    #+#             */
/*   Updated: 2024/06/08 01:07:12 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "minishell.h"
#include "cmd.h"
#include "error_handler.h"
#include "libft.h"
#include "ptr.h"
#include "builtin.h"
#include "txt_utils.h"

static bool	num_in_range(t_string arg)
{
	unsigned long long	value;

	value = ft_atoull(arg);
	if (value > LLONG_MAX)
		return (false);
	return (true);
}

static bool	bultin_exit_is_numeric(t_string arg)
{
	size_t		i;

	if (arg[0] == '\0' || (ft_isdigit(arg[0]) == 0 && arg[0] != '+' && \
			arg[0] != '-'))
		return (false);
	i = 1;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

/*
	arg is numeric
*/
static int	builtin_exit_num_arg(t_minishell *shell, t_string arg, \
				int num_args, bool parent)
{
	t_string	trim_arg;
	long		status;

	if (num_args > 1)
		return (builtin_exit_print_error(\
				"Error: Too many arguments\n", 1));
	trim_arg = builtin_exit_trimarg(arg);
	status = ft_atol(trim_arg);
	if (num_in_range(trim_arg) == false)
	{
		free (trim_arg);
		error_print("Error: A numeric arg is required\n");
		builtin_exit_and_free(shell, 2, parent);
	}
	free (trim_arg);
	builtin_exit_and_free(shell, status, parent);
	return (EXIT_SUCCESS);
}

int	builtin_exit(t_minishell *shell, t_cmd cmd, bool parent)
{
	t_list		*node;
	t_token		*token;
	size_t		num_args;

	num_args = ft_lstsize(cmd.args);
	node = cmd.args;
	if (node)
	{
		token = (t_token *)node->content;
		if (bultin_exit_is_numeric(token->value))
			return (builtin_exit_num_arg(shell, token->value, \
						num_args, parent));
		else
		{
			error_print("Error: A numeric arg is required\n");
			builtin_exit_and_free(shell, 2, parent);
		}
	}
	return (builtin_exit_and_free(shell, EXIT_SUCCESS, parent));
}
