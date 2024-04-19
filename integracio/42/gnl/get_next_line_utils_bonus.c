/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:11:43 by abluis-m          #+#    #+#             */
/*   Updated: 2024/01/04 21:01:30 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	*ft_calloc(size_t nelem, size_t elsize)
{
	register void	*ptr;
	unsigned char	*bytes;
	size_t			num_bytes;

	if (nelem == 0 || elsize == 0)
	{
		nelem = 1;
		elsize = 1;
	}
	num_bytes = nelem * elsize;
	if (num_bytes / elsize != nelem)
		return (NULL);
	ptr = malloc (num_bytes);
	if (!ptr)
		return (NULL);
	bytes = (unsigned char *)ptr;
	while (num_bytes-- > 0)
		*bytes++ = '\0';
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		l1;
	int		l2;
	int		i;
	char	*join;

	if (!s1)
		s1 = ft_calloc(2, sizeof(char));
	if (!s1)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	join = (char *)ft_calloc((l1 + l2 + 1), sizeof(char));
	if (!join)
		return (ft_free(&s1));
	i = -1;
	while (s1[++i])
		join[i] = s1[i];
	i = -1;
	while (s2[++i])
		join[i + l1] = s2[i];
	free(s1);
	return (join);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != c)
		s++;
	if (*s == c)
		return ((char *)s);
	else
		return (NULL);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		sub = malloc(sizeof(char) * (1));
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (start < ft_strlen(s) && i < len && s[start])
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
