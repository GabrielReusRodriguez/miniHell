/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:28:42 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/23 23:46:59 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

t_token_set	tokens_new(void)
{
	t_token_set	token_set;

	token_set.last_read_token = NULL;
	token_set.tokens = NULL;
	token_set.total = 0;
	return (token_set);
}

void	token_free(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	free (token->value);
	free (token);
}

bool	tokens_isword(t_token token)
{
	if (token.type == TOKEN_TYPE_WORD || \
			token.type == TOKEN_TYPE_WORD_SQUOTE || \
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
	return (new_token);
}
