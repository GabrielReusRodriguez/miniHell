/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:31:43 by gabriel           #+#    #+#             */
/*   Updated: 2024/06/01 00:32:25 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "var.h"
#include "ptr.h"
#include "expansor.h"

#include <stdio.h>

t_var	var_new(void)
{
	t_var	var;

	var.key = NULL;
	var.value = NULL;
	return (var);
}

t_var	*var_init(t_string str, t_var *var)
{
	size_t	size;
	int		initial_pos;

	size = ft_strlen(str);
	initial_pos = ft_istrchr(str, "=");
	if (initial_pos <= 0)
		return (NULL);
	var->key = ft_substr(str, 0, initial_pos);
	ptr_check_malloc_return(var->key, "Error at memory malloc.\n");
	if (var_has_valid_name(var->key) == false)
	{
		var_destroy(var);
		return (NULL);
	}
	var->value = ft_substr(str, initial_pos + 1, size);
	ptr_check_malloc_return(var->value, "Error at memory malloc.\n");
	return (var);
}

t_var	*var_clone(t_var var)
{
	t_var	*new_var;

	new_var = (t_var *)safe_malloc(sizeof (t_var));
	new_var->key = ft_strdup(var.key);
	ptr_check_malloc_return(new_var->key, "Error at memory malloc.\n");
	new_var->value = ft_strdup(var.value);
	ptr_check_malloc_return(new_var->value, "Error at memory malloc.\n");
	return (new_var);
}

t_string	var_2_string(t_var var)
{
	t_string	str;
	t_string	aux;

	aux = ft_strjoin(var.key, "=");
	ptr_check_malloc_return(aux, "Error at memory malloc.\n");
	str = ft_strjoin(aux, var.value);
	ptr_check_malloc_return(str, "Error at memory malloc.\n");
	free (aux);
	return (str);
}

void	var_destroy(t_var	*var)
{
	if (var == NULL)
		return ;
	if (var->value != NULL)
	{
		free(var->value);
		var->value = NULL;
	}
	if (var->key != NULL)
	{
		free(var->key);
		var->key = NULL;
	}
}
