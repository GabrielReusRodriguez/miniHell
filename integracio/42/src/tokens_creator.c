/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 08:27:32 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/19 08:50:53 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*token_new_word(char *str, size_t *final_pos)
{
	t_token		*token;
	size_t		i;
	size_t		word_init;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	i = 0;
	if (str[i] == '\0')
	{
		token->type = TOKEN_TYPE_EMPTY;
		token->value = NULL;
		*final_pos = *final_pos + i;
		return (ft_lstnew(token));
	}
	word_init = i;
	while (str[i] != '\0' && parser_charinset(str[i], PARSER_SEPARATORS) \
				== false)
		i++;
	token->type = TOKEN_TYPE_WORD;
	token->value = ft_substr(str, word_init, i - word_init);
	if (token->value == NULL)
		return (NULL);
	*final_pos = *final_pos + i;
	return (ft_lstnew(token));
}

t_list	*token_new_pipe(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_PIPE;
	token->value = ft_strdup("|");
	if (token->value == NULL)
		return (NULL);
	(*i)++;
	return (ft_lstnew(token));
}

t_list	*token_new_semicolon(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_SEMICOLON;
	token->value = ft_strdup(";");
	if (token->value == NULL)
		return (NULL);
	(*i)++;
	return (ft_lstnew(token));
}

t_list	*token_new_redtruncate(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_RED_TRUNCATE;
	token->value = ft_strdup(">");
	if (token->value == NULL)
		return (NULL);
	(*i)++;
	return (ft_lstnew(token));
}

t_list	*token_new_redappend(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_RED_APPEND;
	token->value = ft_strdup(">>");
	if (token->value == NULL)
		return (NULL);
	(*i) = *i + 2;
	return (ft_lstnew(token));
}

/*
t_list  *token_new_paropen(size_t *i)
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

t_list  *token_new_parclose(size_t *i)
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
*/
