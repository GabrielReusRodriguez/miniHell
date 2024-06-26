/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 23:12:23 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/31 00:07:21 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"
#include "libft.h"
#include "ptr.h"

t_string	text_join(t_string origin, t_string destiny)
{
	t_string	res;

	res = ft_strjoin(origin, destiny);
	ptr_check_malloc_return(res, "Error at memory malloc.\n");
	free (origin);
	free (destiny);
	return (res);
}
