/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:06:42 by greus-ro          #+#    #+#             */
/*   Updated: 2024/06/09 18:28:12 by greus-ro         ###   ########.fr       */
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

#include <stdio.h>

/*
	With positive values, bash of 42 mac
	compares the value with ullong_max
*/
static bool	num_in_range(t_string arg)
{
	unsigned long long	value;
	bool				is_negative;

	is_negative = false;
	if (arg[0] == '-')
		is_negative = true;
	value = ft_atoull(arg);
	if (is_negative)
	{
		if (value > ((unsigned long long)LLONG_MAX) + 1)
			return (false);
	}
	else
	{
		if (value > LLONG_MAX)
			return (false);
	}
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
static int	builtin_exit_num_arg(t_minishell *shell, t_string trim_arg, \
				int num_args, bool parent)
{
	long		status;

	if (num_args > 1)
	{
		free (trim_arg);
		return (builtin_exit_print_error(\
				"Error: Too many arguments\n", 1));
	}
	if (num_in_range(trim_arg) == false)
	{
		free (trim_arg);
		error_print("Error: A numeric arg is required\n");
		builtin_exit_and_free(shell, 2, parent);
	}
	status = ft_atol(trim_arg);
	free (trim_arg);
	builtin_exit_and_free(shell, status, parent);
	return (EXIT_SUCCESS);
}

int	builtin_exit(t_minishell *shell, t_cmd cmd, bool parent)
{
	t_list		*node;
	t_token		*token;
	size_t		num_args;
	t_string	trim_arg;

	num_args = ft_lstsize(cmd.args);
	node = cmd.args;
	if (node)
	{
		token = (t_token *)node->content;
		trim_arg = ft_strtrim(token->value, " \t\n\v");
		ptr_check_malloc_return(trim_arg, "Error at memory malloc.");
		if (bultin_exit_is_numeric(trim_arg))
			return (builtin_exit_num_arg(shell, trim_arg, \
						num_args, parent));
		else
		{
			free(trim_arg);
			error_print("Error: A numeric arg is required\n");
			builtin_exit_and_free(shell, 2, parent);
		}
	}
	return (builtin_exit_and_free(shell, EXIT_SUCCESS, parent));
}
