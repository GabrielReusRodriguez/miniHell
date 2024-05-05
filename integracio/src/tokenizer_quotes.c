/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:32:11 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/05 21:25:05 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

t_list	*tokenizer_new_token(int type, t_string value)
{
	t_token	*token;
	t_list	*token_node;

	if (value == NULL)
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->value = value;
	token_node = ft_lstnew(token);
	if (token_node == NULL)
		return (token_free(token));
	return (token_node);
}

t_list	*tokenizer_new_dquote(t_string str, size_t *pos)
{
	size_t	i;
	t_list	*token_node;

	if (tokenizer_ischarclosed(str, *pos, '\"') == false)
	{
	/*	token_node = tokenizer_new_token(TOKEN_TYPE_WORD_DQUOTE, \
					ft_strdup("\""));
		if (token_node == NULL)
			return (NULL);
            */
		token_node =tokenizer_new_token(TOKEN_TYPE_EMPTY, \
					NULL);
		if (token_node == NULL)
			return (NULL);					
		(*pos)++;
		return (token_node);
	}
	i = 1;
	while (str[*pos + i] != '\0' && str[*pos + i] != '\"')
		i++;
	token_node = tokenizer_new_token(TOKEN_TYPE_WORD_DQUOTE, \
					ft_substr(str, *pos + 1, i - 1));
	if (token_node == NULL)
		return (NULL);
	*pos = *pos + i + 1;
	return (token_node);
}

t_list	*tokenizer_new_squote(t_string str, size_t *pos)
{
	t_list	*token_node;
	size_t	i;

    printf("Nuevo squote\n");
	if (tokenizer_ischarclosed(str, *pos, '\'') == false)
	{
	/*	token_node = tokenizer_new_token(TOKEN_TYPE_WORD_DQUOTE, \
					ft_strdup("\'"));
		if (token_node == NULL)
			return (NULL);
            */
		token_node = tokenizer_new_token(TOKEN_TYPE_EMPTY, \
					NULL);
		if (token_node == NULL)
			return (NULL);
		(*pos)++;
		return (token_node);
	}
	i = 1;
	while (str[*pos + i] != '\0' && str[*pos + i] != '\'')
		i++;
	token_node = tokenizer_new_token(TOKEN_TYPE_WORD_SQUOTE, \
					ft_substr(str, *pos + 1, i - 1));
	if (token_node == NULL)
		return (NULL);
	*pos = *pos + i + 1;
	return (token_node);
}
/*
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
*/
