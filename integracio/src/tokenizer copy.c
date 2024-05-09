/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:26:04 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/09 20:19:58 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "parser.h"
#include "environment.h"
#include "expansor.h"

static void    tokenizer_add_space(t_token_set *token_set)
{
	t_list		*node;
    t_token     *token;
    
    node = tokenizer_new_token(TOKEN_TYPE_EMPTY, \
					NULL);
    ft_lstadd_back(&token_set->tokens, node);
}

t_token_set	tokenizer(t_string str, t_environment *env)
{
	t_token_set	token_list;
	t_list		*node;
	size_t		i;

	i = 0;
	token_list = token_set_new();
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
    if (str[*pos] == '(')
		return (tokenizer_new_paropen(pos));
        */
	if (str[*pos] == '<' && str[*pos + 1] == '<')
		return (tokenizer_new_redheredoc(pos));
	if (str[*pos] == '<')
		return (tokenizer_new_redinput(pos));
	if (str[*pos] == '>' && str[*pos + 1] == '>')
		return (tokenizer_new_redappend(pos));
	if (str[*pos] == '>')
		return (tokenizer_new_redtruncate(pos));
	/*
    if (str[*pos] == ')')
		return (tokenizer_new_parclose(pos));
        */
	return (tokenizer_new_word(str + *pos, pos));
}

