/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:23:44 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/16 22:10:04 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"
#include "expansor.h"
#include "libft.h"

/*
	Para validar el formato de variable lo hacemos con la funcion vars_find_end
	ya que asi tenemos centralizado en una funcion el formato de var.
*/
bool    var_has_valid_name(t_string key)
{
	size_t  len;
	size_t  end_var;

	len = ft_strlen(key);
	end_var  = expansor_vars_find_end_var(key, 0);
	if (len == end_var)
		return (true);
	return (false);
}