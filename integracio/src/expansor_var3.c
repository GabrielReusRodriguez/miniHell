/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_var3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:04:11 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/12 23:47:50 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"
#include "environment.h"
#include "error_handler.h"
#include "tokens.h"
#include "ptr.h"
#include "expansor.h"
#include "txt_utils.h"

#include <stdio.h>

t_string	expansor_vars_join_acumulated(t_string acum, t_expansor limits)
{
	t_string	res;
	t_string	substring;

	substring = ft_substr(limits.str, limits.init, limits.i - limits.init);
	if (substring == NULL)
		error_system_crash("Error at memory malloc\n");
	res = text_join(acum, substring);
	return (res);
}
