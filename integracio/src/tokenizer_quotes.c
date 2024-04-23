/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:32:11 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/23 23:42:57 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

t_list	*tokenizer_new_dquote(t_string str, size_t *pos)
{
	t_token	*token;
	size_t	i;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	if (tokenizer_ischarclosed(str, *pos, '\"') == false)
	{
		token->type = TOKEN_TYPE_EMPTY;
		token->value = ft_strdup("\"");
		if (token->value == NULL)
			return (NULL);
		(*pos)++;
		return (ft_lstnew(token));
	}
	i = 1;
	while (str[*pos + i] != '\0' && str[*pos + i] != '\"')
		i++;
	token->type = TOKEN_TYPE_WORD_DQUOTE;
	token->value = ft_substr(str, *pos, i + 1);
	if (token->value == NULL)
		return (NULL);
	*pos = *pos + i + 1;
	return (ft_lstnew(token));
}

t_list	*tokenizer_new_squote(t_string str, size_t *pos)
{
	t_token	*token;
	size_t	i;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	if (tokenizer_ischarclosed(str, *pos, '\'') == false)
	{
		token->type = TOKEN_TYPE_EMPTY;
		token->value = ft_strdup("\'");
		if (token->value == NULL)
			return (NULL);
		(*pos)++;
		return (ft_lstnew(token));
	}
	i = 1;
	while (str[*pos + i] != '\0' && str[*pos + i] != '\'')
		i++;
	token->type = TOKEN_TYPE_WORD_SQUOTE;
	token->value = ft_substr(str, *pos, i + 1);
	if (token->value == NULL)
		return (NULL);
	*pos = *pos + i + 1;
	return (ft_lstnew(token));
}
