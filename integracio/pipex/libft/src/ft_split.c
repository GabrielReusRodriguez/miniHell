/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:13:31 by abluis-m          #+#    #+#             */
/*   Updated: 2023/10/19 12:04:28 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nextdel(char const *s, char d, int i)
{
	while (s[i] && s[i] != d)
		i++;
	return (i);
}

static int	ft_nextword(char const *s, char d, int i)
{
	while (s[i] && s[i] == d)
		i++;
	return (i);
}

static int	ft_countwords(char const *s, char d)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != d)
		{
			words++;
			i = ft_nextdel(s, d, i);
		}
		else
			i++;
	}
	return (words);
}

static void	ft_clearsplit(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		size;
	int		i;
	int		j;

	size = ft_countwords(s, c) + 1;
	split = (char **)malloc(sizeof(char *) * size);
	if (!s || !split)
		return (NULL);
	i = 0;
	j = 0;
	while (j < size - 1)
	{
		i = ft_nextword(s, c, i);
		split[j] = ft_substr(s, i, ft_nextdel(s, c, i) - i);
		if (!split[j])
		{
			ft_clearsplit(split);
			return (NULL);
		}
		i = ft_nextdel(s, c, i);
		j++;
	}
	split[j] = NULL;
	return (split);
}
