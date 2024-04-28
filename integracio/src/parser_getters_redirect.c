/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_getters_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:32:23 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/29 01:00:20 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"

t_token	*parser_get_redir_input(t_list *token_list_node, t_list *end_cmd)
{
	t_token	*token;
	t_token *token_redirect_type;
	t_list	*node;

	if (token_list_node == NULL || token_list_node == end_cmd)
		return (NULL);
	token_redirect_type = NULL;
	node = token_list_node;
	while (node != NULL && node != end_cmd)
	{
		token = (t_token *)(node)->content;
		if (token->type == TOKEN_TYPE_RED_INPUT || \
				token->type == TOKEN_TYPE_RED_HERE_DOC)
			token_redirect_type = (t_token *)node->content;
		node = node->next;
	}
	return (token_redirect_type);
}

/*
	En esta función, buscamos el origen de la redireccion. 
	Primero revisamos que el inicio de la lista, el final de la lista 
	no sean null y que el token de redireccion no sea null. 

	Esto último significa que hemos detectado una redirección antes...
	
	1. Avanzamos en la lista de tokens hasta encontrar el token de redireccion
	2. Eliminamos los tokens no tratables (parentesis)
	3. si lo que tenemos es una WORD, esa ES nuestro origen.
*/
t_token	*parser_get_redir_input_origin(t_list *token_list_node, \
				t_list *end_cmd, t_token *token_red_type)
{
	t_list	*node;
	t_token	*token;

	if (token_list_node == NULL ||	token_list_node == end_cmd || \
			token_red_type == NULL)
		return (NULL);
	node = tokens_goto(token_list_node, token_red_type, end_cmd);
	while (node != NULL && node != end_cmd)
	{
		token = node->content;
		if (tokens_isword(*token) == true)
			return (token);
		node = node->next;
	}
	return (NULL);
}

t_token	*parser_get_redir_output(t_list *token_list_node, t_list *end_cmd)
{
	t_token	*token;
	t_token *token_redirect_type;
	t_list	*node;

	if (token_list_node == NULL || token_list_node == end_cmd)
		return (NULL);
	token_redirect_type = NULL;
	node = token_list_node;
	while (node != NULL && node != end_cmd)
	{
		token = (t_token *)(node)->content;
		if (token->type == TOKEN_TYPE_RED_APPEND || \
				token->type == TOKEN_TYPE_RED_TRUNCATE)
			token_redirect_type = (t_token *)node->content;
		node = node->next;
	}
	return (token_redirect_type);
}

t_token	*parser_get_redir_output_dest(t_list *token_list_node, \
			t_list *end_cmd, t_token *token_red_type)
{
	t_list	*node;
	t_token	*token;

	if (token_list_node == NULL ||	token_list_node == end_cmd || \
			token_red_type == NULL)
		return (NULL);
	node = tokens_goto(token_list_node, token_red_type, end_cmd);
	while (node != NULL && node != end_cmd)
	{
		token = node->content;
		if (tokens_isword(*token) == true)
			return (token);
		node = node->next;
	}
/*
	if (node->content == token_red_type)
	{
		token = parse_avoid_unparse_tokens(node->next, end_cmd);
		if (token == NULL)
			return (NULL);
		if (tokens_isword(*token) == true)
			return (token);
	}
*/
	return (NULL);
}
