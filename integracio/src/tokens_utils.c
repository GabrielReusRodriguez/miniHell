/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:28:42 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/09 22:08:48 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "error_handler.h"

t_token *token_new(int type, t_string value)
{
    t_token *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (token == NULL)
        error_system_crash("Error at memory malloc\n");
    token->type = type;
    token->value = value;
    return (token);
}

/*
t_token_set	tokens_new(void)
{
	t_token_set	token_set;

	token_set.last_read_token = NULL;
	token_set.tokens = NULL;
	token_set.total = 0;
	return (token_set);
}
*/
void	*token_free(t_token *token)
{
	if (token != NULL)
	{
		if (token->value != NULL)
			free (token->value);
		free (token);
	}
	return (NULL);
}

bool	tokens_isword(t_token token)
{
	if (token.type == TOKEN_TYPE_WORD || \
			token.type == TOKEN_TYPE_WORD_DQUOTE || \
			token.type == TOKEN_TYPE_WORD_SQUOTE)
		return (true);
	return (false);
}

t_token	*tokens_clone(t_token token)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->type = token.type;
	new_token->value = ft_strdup(token.value);
	if (new_token->value == NULL)
		return (token_free(new_token));
	return (new_token);
}

void	token_free_node(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	if (token != NULL)
	{
		if (token->value != NULL)
			free (token->value);
		free (token);
	}
}
