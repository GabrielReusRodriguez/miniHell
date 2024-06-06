/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:23:44 by gabriel           #+#    #+#             */
/*   Updated: 2024/06/06 21:56:01 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"
#include "expansor.h"
#include "libft.h"
#include "ptr.h"

/*
	To check the format of var, we do with the function var_find_end
	to use always the same function.

	
*/
bool	var_has_valid_name(t_string key)
{
	size_t	len;
	size_t	end_var;

	len = ft_strlen(key);
	end_var = expansor_vars_find_end_var(key, 0);
	if (len == end_var)
		return (true);
	return (false);
}

t_var	var_new_wargs(t_string key, t_string value)
{
	t_var	var;

	var.key = ft_strdup(key);
	ptr_check_malloc_return(var.key, "Error at memory malloc.\n");
	var.value = ft_strdup(value);
	ptr_check_malloc_return(var.value, "Error at memory malloc.\n");
	return (var);
}
