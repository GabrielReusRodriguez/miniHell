/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 00:00:25 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/11 01:53:29 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"
#include "error_handler.h"

#include <stdio.h>

t_list	*tokenizer_new_word(t_string str, size_t *final_pos)
{
	t_token		*token;
	size_t		i;
	size_t		word_init;
	t_list		*token_node;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	i = 0;
	word_init = i;
	while (str[i] != '\0' && tokenizer_charinset(str[i], TOKENS_SEPARATORS) \
				== false && tokenizer_charinset(str[i], PARSER_CMD_SEPARATORS) \
				== false && tokenizer_charinset(str[i], "\"\'") \
				== false)
		i++;
	token->type = TOKEN_TYPE_WORD;
	token->value = ft_substr(str, word_init, i - word_init);
	if (token->value == NULL)
		return (token_free(token));
	*final_pos = *final_pos + i;
	token_node = ft_lstnew(token);
	if (token_node == NULL)
		return (token_free(token));
	return (token_node);
}
