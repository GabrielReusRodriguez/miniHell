/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:58:37 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/13 20:56:47 by gabriel          ###   ########.fr       */
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
	printf("INICIO DEBUG Tokens: \n");
	node = tokens.tokens;
	while (node != NULL)
	{
		printf("\t NODE value : _%s_\n", ((t_token *)node->content)->value);
		printf("\t NODE type : _%d_\n", ((t_token *)node->content)->type);
		node = node->next;
	}
	printf("FIN DEBUG Tokens \n");
}

void	ft_token_destroy_tokenlist(t_token_set *list)
{
//	ft_lstclear(&list->tokens, free);
	ft_lstclear(&list->tokens, ft_token_free);
	//list->tokens = NULL;
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
	/*
	while (str[i] != '\0' && ft_parser_charinset(str[i],PARSER_SEPARATORS) \
				== TRUE)
		i++;
		*/
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
		while(ft_parser_charinset(str[i], PARSER_SEPARATORS))
			i++;
		node = ft_token_get_next_token(str, &i);
		if (node == NULL)
		{
			ft_token_destroy_tokenlist(&token_list);
			return (token_list);
		}
		ft_lstadd_back(&token_list.tokens, node);
		token_list.total++;
			/*
		if (str[i] == '|')
		{
			node = ft_token_new_pipe(&i);
			if (node == NULL)
			{
				ft_token_destroy_tokenlist(&token_list);
				return (token_list);
			}
			ft_lstadd_back(&token_list.tokens, node);
			token_list.total++;
			i++;
			continue;
		}
		if (str[i] == '\"')
		{
			continue;
		}
		node = ft_token_new_word(str + i, &i);
		if (node == NULL)
		{
			ft_token_destroy_tokenlist(&token_list);
			return (token_list);
		}
		ft_lstadd_back(&token_list.tokens, node);
		token_list.total++;
		i++;
		*/
	}
	ft_token_debug(token_list);
	return (token_list);
}

/*
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
		while(ft_parser_charinset(str[i], PARSER_SEPARATORS))
			i++;
		if (str[i] == '|')
		{
			node = ft_token_new_pipe(&i);
			if (node == NULL)
			{
				ft_token_destroy_tokenlist(&token_list);
				return (token_list);
			}
			ft_lstadd_back(&token_list.tokens, node);
			token_list.total++;
			i++;
			continue;
		}
		if (str[i] == '\"')
		{
			continue;
		}
		node = ft_token_new_word(str + i, &i);
		if (node == NULL)
		{
			ft_token_destroy_tokenlist(&token_list);
			return (token_list);
		}
		ft_lstadd_back(&token_list.tokens, node);
		token_list.total++;
		i++;
	}
	ft_token_debug(token_list);
	return (token_list);
}
*/


/*
t_list	*ft_token_new(t_string str, int *final_pos);
{
	size_t	i;
	t_list	*node;

	i = 0;
	
	if (str[i] == '\"')
	{
		node = ft_token_new_dquotes();
	}
	if (str[i] == '\'')
	{
		node = ft_token_new_squotes();
	}
	if (str[i] == '&' && str[i + 1] == '&')
	{
		node = ft_token_new_and();
	}
	if (str[i] == '|')
	{
		if (str[i + 1] == '|')
		{
			node = ft_token_new_or();
		}
		else
		{
			node = ft_token_new_pipe();	
		}
	}
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
		{
			node = ft_token_new_heredoc();
		}
		else
		{
			node = ft_token_new_redinput();
		}
	}
	if (str[i] == '>' && str[i + 1] == '>')
	{
		node = ft_token_new_append();
	}
	if (str[i] == ';')
	{
		node = ft_token_new_semicolon();
	}
	node = ft_token_new_word(str, &i);
	return (node);
}
*/

