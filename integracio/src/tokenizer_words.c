/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 00:00:25 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/25 18:25:38 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "tokens.h"
#include "parser.h"
#include "error_handler.h"
#include "ptr.h"

/*
	We found a new word, so we create a token with type word.
	it includes all letter until we get a space, tab , pipe or 
	quote.
*/

t_list	*tokenizer_new_word(t_string str, size_t *final_pos)
{
	t_token		*token;
	size_t		i;
	size_t		word_init;
	t_list		*token_node;

	token = (t_token *)safe_malloc(sizeof(t_token));
	i = 0;
	word_init = i;
	while (str[i] != '\0' && tokenizer_charinset(str[i], TOKENS_SEPARATORS) \
				== false && tokenizer_charinset(str[i], PARSER_CMD_SEPARATORS) \
				== false && tokenizer_charinset(str[i], "\"\'") \
				== false)
		i++;
	token->type = TOKEN_TYPE_WORD;
	token->value = ft_substr(str, word_init, i - word_init);
	ptr_check_malloc_return(token->value, "Error at memory malloc.\n");
	*final_pos = *final_pos + i;
	token_node = ft_lstnew(token);
	ptr_check_malloc_return(token_node, "Error at memory malloc.\n");
	return (token_node);
}
