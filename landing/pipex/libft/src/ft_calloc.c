/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:49:32 by abluis-m          #+#    #+#             */
/*   Updated: 2024/01/04 10:58:43 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*bytes;
	size_t	size;

	size = nelem * elsize;
	bytes = malloc(size);
	if (!bytes)
		return (NULL);
	ft_bzero(bytes, size);
	return (bytes);
}
/*
	if (nelem == 0 || elsize == 0)
	{
		nelem = 1;
		elsize = 1;
	}
	size = nelem * elsize;
	if (size / elsize != nelem)
		return (NULL);
*/
