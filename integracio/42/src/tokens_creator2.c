/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 08:27:32 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/19 08:52:54 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*token_new_redinput(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_RED_INPUT;
	token->value = ft_strdup("<");
	if (token->value == NULL)
		return (NULL);
	(*i)++;
	return (ft_lstnew(token));
}

t_list	*token_new_redheredoc(size_t *i)
{
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_RED_HERE_DOC;
	token->value = ft_strdup("<<");
	if (token->value == NULL)
		return (NULL);
	(*i) = *i + 2;
	return (ft_lstnew(token));
}

bool	token_isquoteclosed(char *str, size_t pos, char quote)
{
	size_t	i;

	i = 1;
	while (str[pos + i] != quote && str[pos + i] != '\0')
		i++;
	if (str[pos + i] == quote)
		return (true);
	else
		return (false);
}

t_list	*token_new_squote(char *str, size_t *pos)
{
	t_token	*token;
	size_t	i;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	if (token_isquoteclosed(str, *pos, '\'') == false)
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
	token->value = ft_substr(str, *pos, i + 1);
	if (token->value == NULL)
		return (NULL);
	*pos = *pos + i + 1;
	return (ft_lstnew(token));
}

t_list	*token_new_dquote(char *str, size_t *pos)
{
	t_token	*token;
	size_t	i;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	if (token_isquoteclosed(str, *pos, '\"') == false)
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
	token->value = ft_substr(str, *pos, i + 1);
	if (token->value == NULL)
		return (NULL);
	*pos = *pos + i + 1;
	return (ft_lstnew(token));
}
