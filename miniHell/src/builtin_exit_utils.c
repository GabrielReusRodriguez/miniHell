/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 22:43:33 by gabriel           #+#    #+#             */
/*   Updated: 2024/06/07 23:20:53 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"
#include "libft.h"
#include "minishell.h"
#include "error_handler.h"
#include "ptr.h"

t_string	builtin_exit_trimarg(t_string str)
{
	t_string	trim_arg;

	trim_arg = ft_strtrim(str, " \t\n\v");
	ptr_check_malloc_return(trim_arg, "Error at memory malloc.\n");
	return (trim_arg);
}

/*
	YASFTAN
	Yet Another Stupid Function To Avoid Norminette
*/
int	builtin_exit_print_error(t_string msg, int result)
{
	error_print(msg);
	return (result);
}

int	builtin_exit_and_free(t_minishell *shell, int status, \
				bool free_rscs)
{
	if (free_rscs)
		minishell_destroy(*shell);
	exit(status);
}
