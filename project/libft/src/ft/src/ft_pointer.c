/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:46:11 by greus-ro          #+#    #+#             */
/*   Updated: 2024/02/10 01:31:04 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_ptr_free(void *ptr)
{
	if (ptr != NULL)
		free (ptr);
	return (NULL);
}

char	*ft_ptr_new_char_buffer(size_t size)
{
	char	*buffer;

	buffer = ft_calloc(size + 1, 1);
	if (buffer == NULL)
		return (NULL);
	return (buffer);
}
