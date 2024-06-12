/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:04:11 by gabriel           #+#    #+#             */
/*   Updated: 2024/06/12 16:04:16 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"
#include "environment.h"
#include "error_handler.h"
#include "tokens.h"
#include "ptr.h"
#include "expansor.h"
#include "minishell.h"

#include <stdio.h>

/*
	We find the position of the end of the var
	The format var is ${not num}{alphanum | _ }+
*/
size_t	expansor_vars_find_end_var(t_string str, size_t init)
{
	size_t	j;

	j = 0;
	if (str[init + j] == '\0' || !(ft_isalpha(str[init + j]) || \
			tokenizer_charinset(str[init + j], "_")))
		return (0);
	j++;
	while (ft_isalnum(str[init + j]) || tokenizer_charinset(str[init + j], "_"))
		j++;
	return (j);
}

/*
	We get the name of the var . ${name}
*/
t_string	expansor_vars_get_var(t_string str, size_t init, size_t *end_var, \
				t_minishell shell)
{
	t_var		*var;
	t_string	var_key;
	t_string	var_value;
	size_t		size_var;

	size_var = expansor_vars_find_end_var(str, init);
	(*end_var) = init + size_var;
	if (size_var == 0)
	{
		var_value = ft_strdup("");
		ptr_check_malloc_return(var_value, "Error at memory malloc\n");
		return (var_value);
	}
	var_key = ft_substr(str, init, *end_var - init);
	ptr_check_malloc_return(var_key, "Error at memory malloc\n");
	var = env_get_var(shell.cfg.env, var_key);
	if (var != NULL)
		var_value = ft_strdup(var->value);
	else
		var_value = ft_strdup("");
	ptr_check_malloc_return(var_value, "Error at memory malloc\n");
	free (var_key);
	return (var_value);
}
