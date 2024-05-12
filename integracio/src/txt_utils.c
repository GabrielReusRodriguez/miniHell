/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 23:12:23 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/12 23:48:32 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"
#include "libft.h"
#include "error_handler.h"

t_string	text_join(t_string origin, t_string destiny)
{
	t_string	res;

	res = ft_strjoin(origin, destiny);
	free (origin);
	free (destiny);
	if (res == NULL)
		error_system_crash("Error at memory malloc\n");
	return (res);
}
