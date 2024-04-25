/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_getters_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:32:23 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/25 23:43:37 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

t_token *parser_get_redir_input(t_list **token_list_node, t_list *end_cmd)
{
	t_token	*token;

	if (token_list_node == NULL || *token_list_node == NULL || \
            *token_list_node == end_cmd)
		return (NULL);
	token = (t_token *)(*token_list_node)->content;
	if (token->type == TOKEN_TYPE_RED_INPUT || \
			token->type == TOKEN_TYPE_RED_HERE_DOC)
	{
		*token_list_node = (*token_list_node)->next;
		return (token);
	}
	return (NULL);
}

t_token	*parser_get_redir_input_origin(t_list **token_list_node, \
				t_list *end_cmd)
{
	t_token	*token;

	if (token_list_node == NULL || *token_list_node == NULL || \
            *token_list_node == end_cmd)
		return (NULL);
	token = (t_token *)(*token_list_node)->content;
	(*token_list_node) = (*token_list_node)->next;
	return (token);
}

t_token	*parser_get_redir_output(t_list **token_list_node, t_list *end_cmd)
{
	t_token	*token;

	if (token_list_node == NULL || *token_list_node == NULL || \
            *token_list_node == end_cmd)
		return (NULL);
	token = (t_token *)(*token_list_node)->content;
	(*token_list_node) = (*token_list_node)->next;
	return (token);
}

t_token	*parser_get_redir_output_dest(t_list **token_list_node, \
			t_list *end_cmd)
{
	t_token	*token;

	if (token_list_node == NULL || *token_list_node == NULL || \
            *token_list_node == end_cmd)
		return (NULL);
	token = (t_token *)(*token_list_node)->content;
	(*token_list_node) = (*token_list_node)->next;
	return (token);
}