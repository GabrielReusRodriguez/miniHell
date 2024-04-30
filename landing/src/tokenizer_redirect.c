/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:30:05 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/30 19:43:34 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

t_list	*tokenizer_new_redtruncate(size_t *i)
{
	t_token		*token;
	t_list		*token_node;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_RED_TRUNCATE;
	token->value = ft_strdup(">");
	if (token->value == NULL)
		return (token_free(token));
	(*i)++;
	token_node = ft_lstnew(token);
	if (token_node == NULL)
		return (token_free(token));
	return (token_node);
}

t_list	*tokenizer_new_redappend(size_t *i)
{
	t_token		*token;
	t_list		*token_node;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_RED_APPEND;
	token->value = ft_strdup(">>");
	if (token->value == NULL)
		return (token_free(token));
	(*i) = *i + 2;
	token_node = ft_lstnew(token);
	if (token_node == NULL)
		return (token_free(token));
	return (token_node);
}

t_list	*tokenizer_new_redinput(size_t *i)
{
	t_token		*token;
	t_list		*token_node;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_RED_INPUT;
	token->value = ft_strdup("<");
	if (token->value == NULL)
		return (token_free(token));
	(*i)++;
	token_node = ft_lstnew(token);
	if (token_node == NULL)
		return (token_free(token));
	return (token_node);
}

t_list	*tokenizer_new_redheredoc(size_t *i)
{
	t_token		*token;
	t_list		*token_node;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_RED_HERE_DOC;
	token->value = ft_strdup("<<");
	if (token->value == NULL)
		return (token_free(token));
	(*i) = *i + 2;
	token_node = ft_lstnew(token);
	if (token_node == NULL)
		return (token_free(token));
	return (token_node);
}

bool	tokens_is_redir(t_token token)
{
	if (token.type == TOKEN_TYPE_RED_APPEND || \
			token.type == TOKEN_TYPE_RED_HERE_DOC || \
			token.type == TOKEN_TYPE_RED_TRUNCATE || \
			token.type == TOKEN_TYPE_RED_INPUT)
		return (true);
	return (false);
}
