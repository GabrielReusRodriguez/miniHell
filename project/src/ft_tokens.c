/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:58:37 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/21 23:08:09 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "ft_tokens.h"
#include "ft_parser.h"


/*

Metacharacters are: pipe ( | ), ampersand ( & ), semicolon ( ; ), less-than sign ( < ), greater-than sign ( > ), left parenthesis ( ( ), right parenthesis ( ) ), dollar sign ( $ ), backquote ( ` ), backslash ( \ ), right quote ( ' ), double quotation marks ( " ), newline character, space character, and tab character.
*/

void    ft_token_free(void *ptr)
{
	t_token *token;

	token = (t_token*)ptr;
	free (token->value);
	free (token);
}

void	ft_tokens_debug(t_token_set tokens)
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

void	ft_tokens_destroy_tokenlist(t_token_set *list)
{
	ft_lstclear(&list->tokens, ft_token_free);
	list->total = 0;
}

t_list *ft_tokenizer_new_word(t_string str, size_t *final_pos)
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
	while (str[i] != '\0' && ft_tokenizer_charinset(str[i],PARSER_SEPARATORS) \
				== FALSE)
		i++;
	token->type = TOKEN_TYPE_WORD;
	token->value =  ft_substr(str, word_init, i - word_init);
	if (token->value == NULL)
		return (NULL);
	*final_pos = *final_pos + i;
	return (ft_lstnew(token));
}

t_list *ft_tokenizer_new_pipe(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if(token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_PIPE;
	token->value = ft_strdup("|");
	if (token->value == NULL)
		return (NULL);
	(*i)++;
	return (ft_lstnew(token));
}

t_bool	ft_tokenizer_isquoteclosed(t_string str, size_t pos, char quote)
{
	size_t	i;

	i = 1;
	while (str[pos + i] != quote && str[pos + i] != '\0')
		i++;
	if (str[pos + i] == quote)
		return (TRUE);
	else
		return (FALSE);
}

t_list  *ft_tokenizer_new_dquote(t_string str, size_t *pos)
{
	t_token *token;
	size_t  i;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	if (ft_tokenizer_isquoteclosed(str, *pos, '\"') == FALSE)
	{
		token->type = TOKEN_TYPE_EMPTY;
		token->value = ft_strdup("\"");
		if (token->value == NULL)
			return (NULL);
		(*pos)++;
		return (ft_lstnew(token));
	}
	i = 1;
	while (str[*pos + i] != '\0' && str[*pos + i] != '\"')
		i++;
	token->type = TOKEN_TYPE_WORD_DQUOTE;
	token->value =  ft_substr(str, *pos, i + 1);
	if (token->value == NULL)
		return (NULL);
	*pos = *pos + i + 1;
	return (ft_lstnew(token));
}

t_list  *ft_tokenizer_new_semicolon(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if(token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_SEMICOLON;
	token->value = ft_strdup(";");
	if (token->value == NULL)
		return (NULL);
	(*i)++;
	return (ft_lstnew(token));
}

t_list  *ft_tokenizer_new_paropen(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if(token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_PAR_OPEN;
	token->value = ft_strdup("(");
	if (token->value == NULL)
		return (NULL);
	(*i)++;
	return (ft_lstnew(token));
}

t_list  *ft_tokenizer_new_parclose(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if(token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_PAR_CLOSE;
	token->value = ft_strdup(")");
	if (token->value == NULL)
		return (NULL);
	(*i)++;
	return (ft_lstnew(token));
}

t_list  *ft_tokenizer_new_redtruncate(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if(token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_RED_TRUNCATE;
	token->value = ft_strdup(">");
	if (token->value == NULL)
		return (NULL);
	(*i)++;
	return (ft_lstnew(token));
}

t_list  *ft_tokenizer_new_redappend(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if(token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_RED_APPEND;
	token->value = ft_strdup(">>");
	if (token->value == NULL)
		return (NULL);
	(*i) = *i + 2;
	return (ft_lstnew(token));
}

t_list  *ft_tokenizer_new_redinput(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if(token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_RED_INPUT;
	token->value = ft_strdup("<");
	if (token->value == NULL)
		return (NULL);
	(*i)++;
	return (ft_lstnew(token));
}

t_list  *ft_tokenizer_new_redheredoc(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if(token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_RED_HERE_DOC;
	token->value = ft_strdup("<<");
	if (token->value == NULL)
		return (NULL);
	(*i)= *i + 2;
	return (ft_lstnew(token));
}

t_list  *ft_tokenizer_new_squote(t_string str, size_t *pos)
{
	t_token *token;
	size_t  i;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	if (ft_tokenizer_isquoteclosed(str, *pos, '\'') == FALSE)
	{
		token->type = TOKEN_TYPE_EMPTY;
		token->value = ft_strdup("\'");
		if (token->value == NULL)
			return (NULL);
		(*pos)++;
		return (ft_lstnew(token));
	}
	i = 1;
	while (str[*pos + i] != '\0' && str[*pos + i] != '\'')
		i++;
	token->type = TOKEN_TYPE_WORD_SQUOTE;
	token->value =  ft_substr(str, *pos, i + 1);
	if (token->value == NULL)
		return (NULL);
	*pos = *pos + i + 1;
	return (ft_lstnew(token));
}

void	*ft_tokenizer_add_token(t_list *node, t_token_set *token_list)
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

/*
	Si nos encontramos unas comillas, comprobamos que estén cerradas.
	En caso que NO lo estén, simplemente pasamos al siguiente caracter y las ignoramos tal 
	como marca el enunciado.

	Por ahroa comentao el puntoy coma ya que parece que el enunciado dice que 
	lo ignoremos.
*/
t_list	*ft_tokenizer_get_next_token(t_string str, size_t *pos)
{
	if (str[*pos] == '|')
		return(ft_tokenizer_new_pipe(pos));
	if (str[*pos] == '\"')
		return (ft_tokenizer_new_dquote(str, pos));
	if (str[*pos] == '\'')
		return (ft_tokenizer_new_squote(str, pos));
	/*
	if (str[*pos] == ';')
		return (ft_token_new_semicolon(pos));
		*pos++;
	*/
	if (str[*pos] == '(')
		return (ft_tokenizer_new_paropen(pos));
	if (str[*pos] == '<' && str[*pos + 1] == '<')
		return (ft_tokenizer_new_redheredoc(pos));
	if (str[*pos] == '<')
		return (ft_tokenizer_new_redinput(pos));
	if (str[*pos] == '>' && str[*pos + 1] == '>')
		return (ft_tokenizer_new_redappend(pos));
	if (str[*pos] == '>')
		return (ft_tokenizer_new_redtruncate(pos));
	if (str[*pos] == ')')
		return (ft_tokenizer_new_parclose(pos));
	return (ft_tokenizer_new_word(str + *pos, pos));
}

t_token_set	ft_tokenizer(t_string str)
{
	t_token_set	token_list;
	t_list		*node;
	size_t		i;

	i = 0;
	token_list.total = 0;
	token_list.tokens = NULL;
	while (str[i] != '\0')
	{
		while(str[i] != '\0' && ft_tokenizer_charinset(str[i], PARSER_SEPARATORS))
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
	ft_tokens_debug(token_list);
	return (token_list);
}

t_token_set	ft_tokens_new(void)
{
	t_token_set token_set;

	token_set.last_read_token = 	NULL;
	token_set.tokens = NULL,
	token_set.total = 0;
	return (token_set);
}

t_bool	ft_tokens_iscmdseparator(t_token token)
{
	if (token.type == TOKEN_TYPE_AND || token.type == TOKEN_TYPE_OR || \
			token.type == TOKEN_TYPE_PIPE || \
			token.type == TOKEN_TYPE_SEMICOLON)
			return (TRUE);
	return (FALSE);
}

/*
t_cmd	ft_tokens_get_next_comand(t_token_set *token_set)
{
	t_list	*node;
	t_list	*command;
	t_token	*token;
	t_cmd	cmd;

	cmd = ft_cmd_new();
	if (token_set->last_read_token == NULL)
		node = token_set->tokens;
	else
		node = token_set->last_read_token->next;
	cmd.first_token = node;
	while(node != NULL)
	{
		token_set->last_read_token = node;
		token = (t_token *)node->content;
		if (ft_tokens_iscmdseparator(*token) == TRUE)
			break;
		node = node->next;
	}
	cmd.last_token = node;
	return (cmd);
}
*/

t_bool		ft_tokens_isword(t_token token)
{
	if (token.type == TOKEN_TYPE_WORD || \
			token.type == TOKEN_TYPE_WORD_SQUOTE || \
			token.type == TOKEN_TYPE_WORD_SQUOTE)
			return (TRUE);
	return (FALSE);
}

t_token     *ft_tokens_clone(t_token token)
{
	t_token	*new_token;

	new_token = (t_token*)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->type = token.type;
	new_token->value = ft_strdup(token.type);
	return(new_token);
}