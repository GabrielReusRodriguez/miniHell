/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:06:42 by greus-ro          #+#    #+#             */
/*   Updated: 2024/06/04 23:15:28 by greus-ro         ###   ########.fr       */
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

/*
	YASFTAN
	Yet Another Stupid Function To Avoid Norminette
*/
static int	builtin_exit_print_error(t_string msg, int result)
{
	error_print(msg);
	return (result);
}

static int	builtin_exit_and_free(t_minishell *shell, int status, \
				bool free_rscs)
{
	if (free_rscs)
		minishell_destroy(*shell);
	exit(status);
}

/*
static	int	builtin_exit_parent(t_minishell *shell, t_cmd cmd)
{
	t_list	*node;
	t_token	*token;
	size_t	num_args;

	num_args = ft_lstsize(cmd.args);
	node = cmd.args;
	if (node)
	{
		token = (t_token *)node->content;
		if (bultin_exit_is_numeric(token->value))
		{
			if (num_args > 1)
				return (builtin_exit_print_error(\
							"Error: Too many arguments\n", 1));
			builtin_exit_and_free(shell, ft_atoi(token->value));
		}
		else
		{
			error_print("Error: A numeric arg is required\n");
			builtin_exit_and_free(shell, 2);
		}
	}
	return(builtin_exit_and_free(shell, EXIT_SUCCESS));
}
*/

int	builtin_exit(t_minishell *shell, t_cmd cmd, bool parent)
{
	t_list	*node;
	t_token	*token;
	size_t	num_args;

	num_args = ft_lstsize(cmd.args);
	node = cmd.args;
	if (node)
	{
		token = (t_token *)node->content;
		if (bultin_exit_is_numeric(token->value))
		{
			if (num_args > 1)
				return (builtin_exit_print_error(\
							"Error: Too many arguments\n", 1));
			builtin_exit_and_free(shell, ft_atoi(token->value), parent);
		}
		else
		{
			error_print("Error: A numeric arg is required\n");
			builtin_exit_and_free(shell, 2, parent);
		}
	}
	return (builtin_exit_and_free(shell, EXIT_SUCCESS, parent));
}
/*
int	builtin_exit(t_minishell *shell, t_cmd cmd, bool parent)
{
	t_list	*node;
	t_token	*token;
	size_t	num_args;

	(void)shell;
	num_args = ft_lstsize(cmd.args);
	node = cmd.args;
	if (node)
	{
		token = (t_token *)node->content;
		if (bultin_exit_is_numeric(token->value))
		{
			if (num_args > 1)
				return (builtin_exit_print_error(\
							"Error: Too many arguments\n", 1));
			exit(ft_atoi(token->value));
		}
		else
		{
			error_print("Error: A numeric arg is required\n");
			exit(2);
		}
	}
	exit (EXIT_SUCCESS);
}
*/
