/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:26:04 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/10 12:47:45 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "parser.h"
#include "environment.h"
#include "expansor.h"
#include "error_handler.h"

static void    tokenizer_add_space(t_list **token_list)
{
	t_list		*node;
    t_string    space;

    space = ft_strdup("");
    if (space == NULL)
        error_system_crash("Error at memory malloc\n");
    node = tokenizer_new_token_node(TOKEN_TYPE_SPACE, space);
    ft_lstadd_back(token_list, node);
}		

t_token_set	tokenizer(t_string str, t_environment *env)
{
	t_token_set	token_list;
	t_list		*node;
	size_t		i;

    (void)env;
	i = 0;
	token_list = token_set_new();
	while (str[i] != '\0')
	{
		while (tokenizer_charinset(str[i], TOKENS_SEPARATORS) == true)
			i++;
		if (str[i] == '\0')
			break ;
		node = tokenizer_get_next_token(str, &i);
		if (node == NULL)
		{
			tokens_destroy_tokenlist(&token_list);
			return (token_list);
		}
        expansor_vars_replace_vars(node->content,env);
		ft_lstadd_back(&token_list.tokens, node);
		token_list.total++;
        if (tokenizer_charinset(str[i], TOKENS_SEPARATORS))
            tokenizer_add_space(&token_list.tokens);
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


