/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_parenthesis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 22:56:49 by gabriel           #+#    #+#             */
/*   Updated: 2024/04/23 23:42:32 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

t_list	*tokenizer_new_paropen(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_PAR_OPEN;
	token->value = ft_strdup("(");
	if (token->value == NULL)
		return (NULL);
	(*i)++;
	return (ft_lstnew(token));
}

t_list	*tokenizer_new_parclose(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_PAR_CLOSE;
	token->value = ft_strdup(")");
	if (token->value == NULL)
		return (NULL);
	(*i)++;
	return (ft_lstnew(token));
}
