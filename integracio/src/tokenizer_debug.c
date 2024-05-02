/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_debug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 23:19:37 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/02 21:33:29 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "tokens.h"
#include "debug.h"

void	tokens_debug(t_token_set tokens)
{
	t_list	*node;
	t_token	*token;

	if (DEBUG_MODE)
	{
		printf("INICIO DEBUG Tokens: ********************************\n");
		node = tokens.tokens;
		while (node != NULL)
		{
			token = (t_token *)node->content;
			printf("\t NODE value : _%s_\n", token->value);
			printf("\t NODE type : _%d_ ", token->type);
			if (token->type == TOKEN_TYPE_AND)
				printf("AND");
			if (token->type == TOKEN_TYPE_EMPTY)
				printf("EMPTY");
			if (token->type == TOKEN_TYPE_OR)
				printf("OR");
			if (token->type == TOKEN_TYPE_FILE)
				printf("FILE");
			if (token->type == TOKEN_TYPE_PAR_CLOSE)
				printf("PATENTHESIS CLOSE");
			if (token->type == TOKEN_TYPE_PAR_OPEN)
				printf("PARENTHESIS OPEN");
			if (token->type == TOKEN_TYPE_PIPE)
				printf("PIPE");
			if (token->type == TOKEN_TYPE_RED_APPEND)
				printf("REDIRECTION OUT APPEND");
			if (token->type == TOKEN_TYPE_RED_INPUT)
				printf("REDIRECTION IN");
			if (token->type == TOKEN_TYPE_RED_HERE_DOC)
				printf("REDIRECTION IN HEREDOC");
			if (token->type == TOKEN_TYPE_RED_TRUNCATE)
				printf("REDIRECTION OUT TRUNCATE");
			if (token->type == TOKEN_TYPE_SEMICOLON)
				printf("SEMICOLON");
			if (token->type == TOKEN_TYPE_UNKNOWN)
				printf("UNKNOWN");
			if (token->type == TOKEN_TYPE_WORD)
				printf("WORD");
			if (token->type == TOKEN_TYPE_WORD_SQUOTE)
				printf("WORD SQUOTE");
			if (token->type == TOKEN_TYPE_WORD_DQUOTE)
				printf("WORD DQUOTE");
			printf("\n");
			node = node->next;
		}
		printf("FIN DEBUG Tokens ********************************\n");
	}
}
