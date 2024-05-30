/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:30:05 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/31 00:19:10 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "ptr.h"

/*
	We create  a token with type redirection output truncate
*/
t_list	*tokenizer_new_redtruncate(size_t *i)
{
	t_token		*token;
	t_list		*token_node;

	token = (t_token *)safe_malloc(sizeof(t_token));
	token->type = TOKEN_TYPE_RED_TRUNCATE;
	token->value = ft_strdup(">");
	ptr_check_malloc_return(token->value, "Error at memory malloc.\n");
	(*i)++;
	token_node = ft_lstnew(token);
	ptr_check_malloc_return(token_node, "Error at memory malloc.\n");
	return (token_node);
}

/*
	We create a new token with type redirection output append .
*/
t_list	*tokenizer_new_redappend(size_t *i)
{
	t_token		*token;
	t_list		*token_node;

	token = (t_token *)safe_malloc(sizeof(t_token));
	token->type = TOKEN_TYPE_RED_APPEND;
	token->value = ft_strdup(">>");
	ptr_check_malloc_return(token->value, "Error at memory malloc.\n");
	(*i) = *i + 2;
	token_node = ft_lstnew(token);
	ptr_check_malloc_return(token_node, "Error at memory malloc.\n");
	return (token_node);
}

/*
	We create a new token with type redirection input.
*/
t_list	*tokenizer_new_redinput(size_t *i)
{
	t_token		*token;
	t_list		*token_node;

	token = (t_token *)safe_malloc(sizeof(t_token));
	token->type = TOKEN_TYPE_RED_INPUT;
	token->value = ft_strdup("<");
	ptr_check_malloc_return(token->value, "Error at memory malloc.\n");
	(*i)++;
	token_node = ft_lstnew(token);
	ptr_check_malloc_return(token_node, "Error at memory malloc.\n");
	return (token_node);
}

/*
	We create a new token with type redirection heredoc
*/
t_list	*tokenizer_new_redheredoc(size_t *i)
{
	t_token		*token;
	t_list		*token_node;

	token = (t_token *)safe_malloc(sizeof(t_token));
	token->type = TOKEN_TYPE_RED_HERE_DOC;
	token->value = ft_strdup("<<");
	ptr_check_malloc_return(token->value, "Error at memory malloc.\n");
	(*i) = *i + 2;
	token_node = ft_lstnew(token);
	ptr_check_malloc_return(token_node, "Error at memory malloc.\n");
	return (token_node);
}
