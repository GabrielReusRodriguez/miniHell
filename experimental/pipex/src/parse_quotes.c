/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 23:16:55 by abluis-m          #+#    #+#             */
/*   Updated: 2024/04/25 14:50:17 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	if (tab)
		while (tab[i] != NULL)
			i++;
	return (i);
}

static size_t	ft_count_splits(const char *s)
{
	size_t	i;
	int		count;
	int		quote;

	i = 0;
	quote = 0;
	count = 0;
	if (s[0] && s[0] != ' ')
		count ++;
	while (s[i])
	{
		if (s[i] == '\'')
			quote++;
		if (quote % 2 == 0)
		{
			if (i > 0 && s[i] != ' ' && s[i - 1] == 32)
				count++;
		}
		i++;
	}
	count += quote / 2;
	return (count);
}

static size_t	ft_search_split(const char *s, size_t i)
{
	int	q;

	q = 0;
	while (s[i])
	{
		if (s[i] == '\'' && q == 0)
		{
			q = s[i];
			i++;
		}
		if (s[i] == q)
			q = 0;
		if (s[i] == ' ' && q == 0)
			return (i);
		i++;
	}
	return (i);
}

char	**ft_remove_quotes(char **tab)
{
	int		i;
	char	**clean;

	i = 0;
	clean = safe_malloc((ft_tablen(tab) + 1) * sizeof(char *));
	while (tab[i])
	{
		clean[i] = ft_strtrim(tab[i], "\'");
		i++;
	}
	clean[i] = NULL;
	free_tab(tab);
	return (clean);
}

char	**ft_split_quotes(const char *s)
{
	char	**split;
	int		index;
	int		i;
	int		j;

	index = 0;
	i = 0;
	j = 0;
	if (!s || ft_strlen(s) == 0)
		return (NULL);
	split = safe_malloc((ft_count_splits(s) + 1) * sizeof(char *));
	while (i <= (int)ft_strlen(s))
	{
		while (s[i] == ' ')
			i++;
		j = ft_search_split(s, i);
		split[index] = ft_substr(s, i, j - i);
		if (!split)
			return (free_tab(split));
		i = j + 1;
		index++;
	}
	split[index] = NULL;
	split = ft_remove_quotes(split);
	return (split);
}
