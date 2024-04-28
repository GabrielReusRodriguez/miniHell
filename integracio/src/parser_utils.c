/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:59:21 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/28 20:26:50 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "cmd.h"

bool	parser_iscmdseparator(t_token token)
{
	if (token.type == TOKEN_TYPE_SEMICOLON || token.type == TOKEN_TYPE_PIPE || \
			token.type == TOKEN_TYPE_AND || token.type == TOKEN_TYPE_OR)
	{
		return (true);
	}
	return (false);
}

t_list *parse_get_next_word(t_list *first_token, t_list *last_token)
{
	t_list  *word;
	t_list  *node;
	t_token *token;

	word = NULL;
	node = first_token;
	while (node != NULL && node != last_token)
	{
		token = (t_token *)node->content;
		if (token->type == TOKEN_TYPE_WORD || \
				token->type == TOKEN_TYPE_WORD_DQUOTE || \
				token->type == TOKEN_TYPE_WORD_SQUOTE)
		{
			word = node;
		}
		node = node->next;
	}    
	return (word);
}

t_token	*parse_avoid_unparse_tokens(t_list *first_token, t_list *last_token)
{
	t_token	*token;

	while (first_token != NULL && first_token != last_token)
	{
		token = (t_token *)first_token->content;
		if (token->type != TOKEN_TYPE_PAR_OPEN && \
				token->type != TOKEN_TYPE_PAR_CLOSE)
			return (token);
		first_token = first_token->next;
	}
	return (NULL);
}
