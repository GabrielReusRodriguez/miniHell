/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:28:42 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/23 18:59:24 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "error_handler.h"
#include "ptr.h"

/*
	We check if the string has closed quotes.
*/
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

/*
	We check if a char is one of the charset we pass in set.
*/
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

/*
	We validate the line readed ( are quotes closed... ?)
*/
bool	tokenizer_valida_str(t_string str)
{
	size_t	i;
	bool	opened_quote;
	char	quote;

	i = 0;
	opened_quote = false;
	while (str[i] != '\0')
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

/*
	Function to create a token with type and value.
*/
t_list	*tokenizer_new_token_node(int type, t_string value)
{
	t_token	*token;
	t_list	*token_node;

	if (value == NULL)
		return (NULL);
	token = (t_token *)safe_malloc(sizeof(t_token));
	token->type = type;
	token->value = value;
	token_node = ft_lstnew(token);
	ptr_check_malloc_return(token_node, "Error at memory malloc.\n");
	return (token_node);
}
