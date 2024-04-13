/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:58:37 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/13 21:59:04 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "ft_tokens.h"
#include "ft_parser.h"


void    ft_token_free(void *ptr)
{
	t_token *token;

	token = (t_token*)ptr;
	free (token->value);
	free (token);
}

void	ft_token_debug(t_token_set tokens)
{
	t_list	*node;
	t_token	*token;
	
	printf("INICIO DEBUG Tokens: \n");
	node = tokens.tokens;
	while (node != NULL)
	{
		token = (t_token *)node->content;
		printf("\t NODE value : _%s_\n", token->value);
		printf("\t NODE type : _%d_ ", token->type);
		if (token->type == TOKEN_TYPE_AND)
			printf("AND");
		if (token->type == TOKEN_TYPE_EMPTY)
			printf("EMPTY");
		if (token->type == TOKEN_TYPE_OR)
			printf("OR");
		if (token->type == TOKEN_TYPE_FILE)
			printf("FILE");
		if (token->type == TOKEN_TYPE_PAR_CLOSE)
			printf("PATENTHESIS CLOSE");
		if (token->type == TOKEN_TYPE_PAR_OPEN)
			printf("PARENTHESIS OPEN");
		if (token->type == TOKEN_TYPE_PIPE)
			printf("PIPE");
		if (token->type == TOKEN_TYPE_RED_APPEND)
			printf("REDIRECTION OUT APPEND");
		if (token->type == TOKEN_TYPE_RED_INPUT)
			printf("REDIRECTION IN");
		if (token->type == TOKEN_TYPE_RED_HERE_DOC)
			printf("REDIRECTION IN HEREDOC");
		if (token->type == TOKEN_TYPE_RED_TRUNCATE)
			printf("REDIRECTION OUT TRUNCATE");
		if (token->type == TOKEN_TYPE_SEMICOLON)
			printf("SEMICOLON");
		if (token->type == TOKEN_TYPE_UNKNOWN)
			printf("UNKNOWN");
		if (token->type == TOKEN_TYPE_WORD)
			printf("WORD");
		if (token->type == TOKEN_TYPE_WORD_SQUOTE)
			printf("WORD SQUOTE");
		if (token->type == TOKEN_TYPE_WORD_DQUOTE)
			printf("WORD DQUOTE");

		printf("\n");	
		node = node->next;
	}
	printf("FIN DEBUG Tokens \n");
}

void	ft_token_destroy_tokenlist(t_token_set *list)
{
	ft_lstclear(&list->tokens, ft_token_free);
	list->total = 0;
}

t_list *ft_token_new_word(t_string str, size_t *final_pos)
{
	t_token		*token;
	size_t		i;
	size_t		word_init;

	token = (t_token *)malloc(sizeof(t_token));
	if(token == NULL)
		return (NULL);
	i = 0;
	if(str[i] == '\0')
	{
		token->type = TOKEN_TYPE_EMPTY;
		token->value = NULL;
		*final_pos = *final_pos + i;	
		return (ft_lstnew(token));
	}
	word_init = i;
	while (str[i] != '\0' && ft_parser_charinset(str[i],PARSER_SEPARATORS) \
				== FALSE)
		i++;
	token->value =  ft_substr(str, word_init, i - word_init);
	token->type = TOKEN_TYPE_WORD;
	*final_pos = *final_pos + i;
	return (ft_lstnew(token));
}

t_list *ft_token_new_pipe(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if(token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_PIPE;
	token->value = ft_strdup("|");
	(*i)++;
	return (ft_lstnew(token));
}

t_list  *ft_token_new_dquote(t_string str, size_t *pos)
{
	t_token *token;
	size_t  i;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	i = 1;
	while (str[*pos + i] != '\0' && str[*pos + i] != '\"')
		i++;
	token->value =  ft_substr(str, *pos, i + 1);
	token->type = TOKEN_TYPE_WORD_DQUOTE;
	*pos = *pos + i + 1;
	return (ft_lstnew(token));
}

t_list  *ft_token_new_semicolon(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if(token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_SEMICOLON;
	token->value = ft_strdup(";");
	(*i)++;
	return (ft_lstnew(token));
}

t_list  *ft_token_new_paropen(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if(token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_PAR_OPEN;
	token->value = ft_strdup("(");
	(*i)++;
	return (ft_lstnew(token));
}

t_list  *ft_token_new_parclose(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if(token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_PAR_CLOSE;
	token->value = ft_strdup(")");
	(*i)++;
	return (ft_lstnew(token));
}

t_list  *ft_token_new_squote(t_string str, size_t *pos)
{
	t_token *token;
	size_t  i;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	i = 1;
	while (str[*pos + i] != '\0' && str[*pos + i] != '\'')
		i++;
	token->value =  ft_substr(str, *pos, i + 1);
	token->type = TOKEN_TYPE_WORD_SQUOTE;
	*pos = *pos + i + 1;
	return (ft_lstnew(token));
}

void	*ft_token_add_token(t_list *node, t_token_set *token_list)
{
	if (node == NULL)
	{
		ft_token_destroy_tokenlist(token_list);
		return (NULL);
	}
	ft_lstadd_back(&token_list->tokens, node);
	token_list->total++;
	return (token_list);
}

t_list	*ft_token_get_next_token(t_string str, size_t *pos)
{
	if (str[*pos] == '|')
		return(ft_token_new_pipe(pos));
	if (str[*pos] == '\"')
		return (ft_token_new_dquote(str, pos));
	if (str[*pos] == '\'')
		return (ft_token_new_squote(str, pos));
	if (str[*pos] == ';')
		return (ft_token_new_semicolon(pos));
	if (str[*pos] == '(')
		return (ft_token_new_paropen(pos));
	if (str[*pos] == ')')
		return (ft_token_new_parclose(pos));
	return (ft_token_new_word(str + *pos, pos));
}

t_token_set	ft_tokens_tokenize(t_string str)
{
	t_token_set	token_list;
	t_list		*node;
	size_t		i;

	i = 0;
	token_list.total = 0;
	token_list.tokens = NULL;
	while (str[i] != '\0')
	{
		while(str[i] != '\0' && ft_parser_charinset(str[i], PARSER_SEPARATORS))
			i++;
		if (str[i] == '\0')
			break ;
		node = ft_token_get_next_token(str, &i);
		if (node == NULL)
		{
			ft_token_destroy_tokenlist(&token_list);
			return (token_list);
		}
		ft_lstadd_back(&token_list.tokens, node);
		token_list.total++;
	}
	ft_token_debug(token_list);
	return (token_list);
}
