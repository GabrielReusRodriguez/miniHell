/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:26:04 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/27 12:38:30 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "parser.h"

t_token_set	tokenizer(t_string str)
{
	t_token_set	token_list;
	t_list		*node;
	size_t		i;

	i = 0;
	token_list.total = 0;
	token_list.tokens = NULL;
	token_list.last_read_token = NULL;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && tokenizer_charinset(str[i], \
				TOKENS_SEPARATORS) == true)
			i++;
		if (str[i] == '\0')
			break ;
		node = tokenizer_get_next_token(str, &i);
		if (node == NULL)
		{
			tokens_destroy_tokenlist(&token_list);
			return (token_list);
		}
		ft_lstadd_back(&token_list.tokens, node);
		token_list.total++;
	}
	tokens_debug(token_list);
	return (token_list);
}

/*
	Si nos encontramos unas comillas, comprobamos que estén cerradas.
	En caso que NO lo estén, simplemente pasamos al siguiente caracter 
	y las ignoramos tal como marca el enunciado.

	Por ahroa comentao el puntoy coma ya que parece que el enunciado dice que 
	lo ignoremos.
*/
t_list	*tokenizer_get_next_token(t_string str, size_t *pos)
{
	if (str[*pos] == '|')
		return (tokenizer_new_pipe(pos));
	if (str[*pos] == '\"')
		return (tokenizer_new_dquote(str, pos));
	if (str[*pos] == '\'')
		return (tokenizer_new_squote(str, pos));
	/*
	if (str[*pos] == ';')
		return (token_new_semicolon(pos));
		*pos++;
	*/
	if (str[*pos] == '(')
		return (tokenizer_new_paropen(pos));
	if (str[*pos] == '<' && str[*pos + 1] == '<')
		return (tokenizer_new_redheredoc(pos));
	if (str[*pos] == '<')
		return (tokenizer_new_redinput(pos));
	if (str[*pos] == '>' && str[*pos + 1] == '>')
		return (tokenizer_new_redappend(pos));
	if (str[*pos] == '>')
		return (tokenizer_new_redtruncate(pos));
	if (str[*pos] == ')')
		return (tokenizer_new_parclose(pos));
	return (tokenizer_new_word(str + *pos, pos));
}

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
				== false && tokenizer_charinset(str[i], "\"\')") \
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
