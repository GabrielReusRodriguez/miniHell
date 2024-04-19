/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:58:37 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/19 09:03:02 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

/*
Metacharacters are: 
	pipe ( | ), ampersand ( & ), semicolon ( ; ), 
	less-than sign ( < ), greater-than sign ( > ), left parenthesis ( ( ), 
	right parenthesis ( ) ), dollar sign ( $ ), backquote ( ` ), 
	backslash ( \ ), right quote ( ' ), double quotation marks ( " ), 
	newline character, space character, and tab character.
*/

static void	token_free(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	free (token->value);
	free (token);
}

/*

*/
void	token_destroy_tokenset(t_token_set *list)
{
	ft_lstclear(&list->tokens, token_free);
	list->total = 0;
}

void	*token_add_token(t_list *node, t_token_set *token_list)
{
	if (node == NULL)
	{
		token_destroy_tokenset(token_list);
		return (NULL);
	}
	ft_lstadd_back(&token_list->tokens, node);
	token_list->total++;
	return (token_list);
}

/*
	Si nos encontramos unas comillas, comprobamos que estén cerradas.
	En caso que NO lo estén, simplemente pasamos al siguiente caracter 
	y las ignoramos tal como marca el enunciado.

	Por ahroa comentao el puntoy coma ya que parece que el enunciado dice que 
	lo ignoremos.
*/
t_list	*token_get_next_token(char *str, size_t *pos)
{
	if (str[*pos] == '|')
		return (token_new_pipe(pos));
	if (str[*pos] == '\"')
		return (token_new_dquote(str, pos));
	if (str[*pos] == '\'')
		return (token_new_squote(str, pos));
	/*
	if (str[*pos] == ';')
		return (ft_token_new_semicolon(pos));
		*pos++;
	if (str[*pos] == '(')
		return (token_new_paropen(pos));
	if (str[*pos] == ')')
		return (token_new_parclose(pos));
	*/
	if (str[*pos] == '<' && str[*pos + 1] == '<')
		return (token_new_redheredoc(pos));
	if (str[*pos] == '<')
		return (token_new_redinput(pos));
	if (str[*pos] == '>' && str[*pos + 1] == '>')
		return (token_new_redappend(pos));
	if (str[*pos] == '>')
		return (token_new_redtruncate(pos));
	return (token_new_word(str + *pos, pos));
}

t_token_set	tokens_tokenize(char *str)
{
	t_token_set	token_list;
	t_list		*node;
	size_t		i;

	i = 0;
	token_list.total = 0;
	token_list.tokens = NULL;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && \
			parser_charinset(str[i], PARSER_SEPARATORS))
			i++;
		if (str[i] == '\0')
			break ;
		node = token_get_next_token(str, &i);
		if (node == NULL)
		{
			token_destroy_tokenset(&token_list);
			return (token_list);
		}
		ft_lstadd_back(&token_list.tokens, node);
		token_list.total++;
	}
	ft_token_debug(token_list);
	return (token_list);
}
