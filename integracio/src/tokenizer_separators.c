/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_separators.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:38:23 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/24 23:12:11 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

bool	tokens_iscmdseparator(t_token token)
{
	if (token.type == TOKEN_TYPE_AND || token.type == TOKEN_TYPE_OR || \
			token.type == TOKEN_TYPE_PIPE || \
			token.type == TOKEN_TYPE_SEMICOLON)
		return (true);
	return (false);
}

t_list	*tokenizer_new_pipe(size_t *i)
{
	t_token		*token;
	t_list		*token_node;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_PIPE;
	token->value = ft_strdup("|");
	if (token->value == NULL)
		return (token_free(token));
	(*i)++;
	token_node = ft_lstnew(token);
	if (token_node == NULL)
		return (token_free(token));
	return (token_node);
}

t_list	*tokenizer_new_semicolon(size_t *i)
{
	t_token		*token;
	t_list		*token_node;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_SEMICOLON;
	token->value = ft_strdup(";");
	if (token->value == NULL)
		return (token_free(token));
	(*i)++;
	token_node = ft_lstnew(token);
	if (token_node == NULL)
		return (token_free(token));
	return (token_node);
}
