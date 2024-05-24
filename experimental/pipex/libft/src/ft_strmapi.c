/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 19:12:11 by abluis-m          #+#    #+#             */
/*   Updated: 2024/01/04 16:19:37 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	index;
	char			*map;

	len = ft_strlen(s);
	map = malloc(sizeof(char) * (len + 1));
	if (!map)
		return (NULL);
	index = 0;
	while (index < len)
	{
		map[index] = f(index, s[index]);
		index++;
	}
	map[index] = '\0';
	return (map);
}
