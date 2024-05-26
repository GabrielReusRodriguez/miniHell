/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_var3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:04:11 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/25 18:22:18 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"
#include "ptr.h"
#include "expansor.h"
#include "txt_utils.h"

/*
	We join the string cumulated when we replace vars with the new string
	we get expanding vars.
*/
t_string	expansor_vars_join_acumulated(t_string acum, t_expansor limits)
{
	t_string	res;
	t_string	substring;

	substring = ft_substr(limits.str, limits.init, limits.i - limits.init);
	ptr_check_malloc_return(substring, "Error at memory malloc\n.");
	res = text_join(acum, substring);
	return (res);
}
