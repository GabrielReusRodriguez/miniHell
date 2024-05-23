/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 23:12:23 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/23 18:16:11 by gabriel          ###   ########.fr       */
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
	free (origin);
	free (destiny);
	ptr_check_malloc_return(res, "Error at memory malloc.\n");
	return (res);
}
