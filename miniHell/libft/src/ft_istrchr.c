/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:29:03 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/24 21:37:58 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_istrchr(char *src, char *c)
{
	int	pos;
	int	i;

	pos = 0;
	while (src[pos] != '\0')
	{
		i = 0;
		while (c[i] != '\0')
		{
			if (c[i] == src [pos])
				return (pos);
			i++;
		}
		pos++;
	}
	return (-1);
}
