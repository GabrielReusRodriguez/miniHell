/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:14:18 by abluis-m          #+#    #+#             */
/*   Updated: 2024/01/04 16:26:55 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		len;

	str = (char *)s;
	len = ft_strlen(str);
	if ((char)c == '\0')
		return (&str[len]);
	else
	{
		while (len >= 0)
		{
			if (str[len] == (char)c)
				return (&str[len]);
			len--;
		}
	}
	return (NULL);
}
