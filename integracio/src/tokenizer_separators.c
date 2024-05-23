/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_separators.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:38:23 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/23 18:45:59 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "ptr.h"

/*
	We check if the token is one off the separators of cmd
*/
bool	tokens_iscmdseparator(t_token token)
{
	if (token.type == TOKEN_TYPE_AND || token.type == TOKEN_TYPE_OR || \
			token.type == TOKEN_TYPE_PIPE || \
			token.type == TOKEN_TYPE_SEMICOLON)
		return (true);
	return (false);
}

/*
	We create a new token with type pipe.
*/
t_list	*tokenizer_new_pipe(size_t *i)
{
	t_token		*token;
	t_list		*token_node;

	token = (t_token *)safe_malloc(sizeof(t_token));
	token->type = TOKEN_TYPE_PIPE;
	token->value = ft_strdup("|");
	ptr_check_malloc_return(token->value, "Error at memory malloc.\n");
	(*i)++;
	token_node = ft_lstnew(token);
	ptr_check_malloc_return(token_node, "Error at memory malloc.\n");
	return (token_node);
}

/*
	We create a new token with type semicolon.
*/
t_list	*tokenizer_new_semicolon(size_t *i)
{
	t_token		*token;
	t_list		*token_node;

	token = (t_token *)safe_malloc(sizeof(t_token));
	token->type = TOKEN_TYPE_SEMICOLON;
	token->value = ft_strdup(";");
	ptr_check_malloc_return(token->value, "Error at memory malloc.\n");
	(*i)++;
	token_node = ft_lstnew(token);
	ptr_check_malloc_return(token_node, "Error at memory malloc.\n");
	return (token_node);
}
