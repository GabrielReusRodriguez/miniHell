/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:28:42 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/09 22:17:46 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "error_handler.h"

/*
bool	ft_tokens_isword(t_token token)
{
	if (token.type == TOKEN_TYPE_WORD || \
			token.type == TOKEN_TYPE_WORD_SQUOTE || \
			token.type == TOKEN_TYPE_WORD_SQUOTE)
		return (true);
	return (false);
}
*/

void	*tokenizer_add_token(t_list *node, t_token_set *token_list)
{
	if (node == NULL)
	{
		tokens_destroy_tokenlist(token_list);
		return (NULL);
	}
	ft_lstadd_back(&token_list->tokens, node);
	token_list->total++;
	return (token_list);
}

bool	tokenizer_ischarclosed(t_string str, size_t pos, char quote)
{
	size_t	i;

	i = 1;
	while (str[pos + i] != quote && str[pos + i] != '\0')
		i++;
	if (str[pos + i] == quote)
		return (true);
	else
		return (false);
}

bool	tokenizer_charinset(char c, t_string set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (true);
		i++;
	}
	return (false);
}

bool	tokenizer_valida_str(t_string str)
{
	size_t	i;
	bool	opened_quote;
	char	quote;

	i = 0;
	opened_quote = false;
	while(str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (opened_quote == true)
			{
				if (str[i] == quote)
					opened_quote = false;
			}
			else
			{
				quote = str[i];
				opened_quote = true;
			}
		}
		i++;
	}
	return (!opened_quote);
}

t_list	*tokenizer_new_token_node(int type, t_string value)
{
	t_token	*token;
	t_list	*token_node;

	if (value == NULL)
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
        error_system_crash("Error at memory malloc\n");
	token->type = type;
	token->value = value;
	token_node = ft_lstnew(token);
	if (token_node == NULL)
        error_system_crash("Error at memory malloc\n");
	return (token_node);
}

