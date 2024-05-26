/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:26:04 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/25 18:25:44 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "parser.h"
#include "environment.h"
#include "expansor.h"
#include "error_handler.h"
#include "minishell.h"
#include "ptr.h"

/*
	We add the token with type space.
*/
static void	tokenizer_add_space(t_list **token_list)
{
	t_list		*node;
	t_string	space;

	space = ft_strdup("");
	ptr_check_malloc_return(space, "Error at memory malloc.\n");
	node = tokenizer_new_token_node(TOKEN_TYPE_SPACE, space);
	ft_lstadd_back(token_list, node);
}

/*
	We replace vars in the token list.
*/
static void	tokenizer_expand_vars(t_list *list, t_minishell shell)
{
	t_list	*node;

	node = list;
	while (node != NULL)
	{
		if (node->next != NULL)
			expansor_vars_replace_vars(node->content, node->next->content, \
				shell);
		else
			expansor_vars_replace_vars(node->content, NULL, shell);
		node = node->next;
	}
}

/*
	This is the logic loop of the tokenizer. 
	We ignore the spaces tabs...
	when we get something different, we creaete next token 
		it depends the char we get, the type of token.
	We add the toklen to the list and we add a space token if the next
	chars are spaces or tabs.
*/
void	tokenizer_loop(t_string str, t_token_set *token_list)
{
	t_list		*node;
	size_t		i;

	i = 0;
	while (str[i] != '\0')
	{
		while (tokenizer_charinset(str[i], TOKENS_SEPARATORS) == true)
			i++;
		if (str[i] == '\0')
			break ;
		node = tokenizer_get_next_token(str, &i);
		if (node == NULL)
		{
			tokens_destroy_tokenlist(token_list);
			return ;
		}
		ft_lstadd_back(&token_list->tokens, node);
		token_list->total++;
		if (tokenizer_charinset(str[i], TOKENS_SEPARATORS))
			tokenizer_add_space(&token_list->tokens);
	}
}

/*
	This function creates a list of tokens with types from the string (line)
	we read from readline.
*/
t_token_set	tokenizer(t_string str, t_minishell shell)
{
	t_token_set	token_list;

	token_list = token_set_new();
	tokenizer_loop(str, &token_list);
	tokenizer_expand_vars(token_list.tokens, shell);
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
