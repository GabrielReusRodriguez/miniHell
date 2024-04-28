/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:26:13 by abluis-m          #+#    #+#             */
/*   Updated: 2024/01/04 11:42:58 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*buff1;
	unsigned char	*buff2;
	size_t			i;

	if (n == 0)
		return (0);
	buff1 = (unsigned char *)s1;
	buff2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (buff1[i] != buff2[i])
			return (buff1[i] - buff2[i]);
		i++;
	}
	return (0);
}
