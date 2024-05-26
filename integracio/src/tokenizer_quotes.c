/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:32:11 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/25 18:25:10 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "ptr.h"

/*
	We create a new token  of type double quote.
	it is from the first quote until the close quote .
	it ignores simple quotes inside and spaces also.
*/
t_list	*tokenizer_new_dquote(t_string str, size_t *pos)
{
	size_t		i;
	t_list		*token_node;
	t_string	aux;

	if (tokenizer_ischarclosed(str, *pos, '\"') == false)
	{
		token_node = tokenizer_new_token_node(TOKEN_TYPE_EMPTY, NULL);
		if (token_node == NULL)
			return (NULL);
		(*pos)++;
		return (token_node);
	}
	i = 1;
	while (str[*pos + i] != '\0' && str[*pos + i] != '\"')
		i++;
	aux = ft_substr(str, *pos + 1, i - 1);
	ptr_check_malloc_return(aux, "Error at memory malloc.\n");
	token_node = tokenizer_new_token_node(TOKEN_TYPE_WORD_DQUOTE, aux);
	if (token_node == NULL)
		return (NULL);
	*pos = *pos + i + 1;
	return (token_node);
}

/*
	We create a new token  of type single quote.
	it is from the first quote until the close quote .
	it ignores double quotes inside and spaces also.
*/
t_list	*tokenizer_new_squote(t_string str, size_t *pos)
{
	t_list		*token_node;
	size_t		i;
	t_string	aux;

	if (tokenizer_ischarclosed(str, *pos, '\'') == false)
	{
		token_node = tokenizer_new_token_node(TOKEN_TYPE_EMPTY, NULL);
		if (token_node == NULL)
			return (NULL);
		(*pos)++;
		return (token_node);
	}
	i = 1;
	while (str[*pos + i] != '\0' && str[*pos + i] != '\'')
		i++;
	aux = ft_substr(str, *pos + 1, i - 1);
	ptr_check_malloc_return(aux, "Error at memory malloc.\n");
	token_node = tokenizer_new_token_node(TOKEN_TYPE_WORD_SQUOTE, aux);
	if (token_node == NULL)
		return (NULL);
	*pos = *pos + i + 1;
	return (token_node);
}
