/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_getters_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:35:39 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/12 22:56:28 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "cmd.h"
#include "error_handler.h"

static	t_string	parser_parse_word_get_value(t_list **token_list)
{
	t_string	value;
	t_token		*token;
	t_string	aux;

	value = ft_strdup("");
	if (value == NULL)
		error_system_crash("Error en memory malloc\n");
	token = (*token_list)->content;
	while (*token_list != NULL && tokens_isword(*token) == true)
	{
		aux = value;
		value = ft_strjoin(value, token->value);
		free (aux);
		*token_list = (*token_list)->next;
		if (*token_list != NULL)
			token = (*token_list)->content;
	}
	return (value);
}

void	*parser_parse_word(t_list **token_list, t_cmd *cmd)
{
	t_list		*node;
	t_string	value;

	if (cmd->exec == NULL)
	{
		value = parser_parse_word_get_value(token_list);
		cmd->exec = token_new(TOKEN_TYPE_WORD, value);
	}
	else
	{
		value = parser_parse_word_get_value(token_list);
		node = tokenizer_new_token_node(TOKEN_TYPE_WORD, value);
		ft_lstadd_back(&cmd->args, node);
	}
	return (cmd);
}

/*
void	*parser_parse_word(t_list **token_list, t_cmd *cmd)
{
	t_list		*node;
	t_token		*token;
	t_string	value;
	t_string	aux;

	if (cmd->exec == NULL)
	{
		value = ft_strdup("");
		if (value == NULL)
			error_system_crash("Error en memory malloc\n");
		token = (*token_list)->content;
		while (*token_list != NULL && tokens_isword(*token) == true)
		{
			aux = value;
			value = ft_strjoin(value, token->value);
			free (aux);
			*token_list = (*token_list)->next;
			if (*token_list != NULL)
				token = (*token_list)->content;
		}
		cmd->exec = token_new(TOKEN_TYPE_WORD, value);
	}
	else
	{
		value = ft_strdup("");
		if (value == NULL)
			error_system_crash("Error en memory malloc\n");
		token = (*token_list)->content; 
		while (*token_list != NULL && tokens_isword(*token) == true)
		{
			aux = value;
			value = ft_strjoin(value, token->value);
			free (aux);
			*token_list = (*token_list)->next;
			if (*token_list != NULL)
				token = (*token_list)->content;
		}
		node = tokenizer_new_token_node(TOKEN_TYPE_WORD, value);
		ft_lstadd_back(&cmd->args, node);
	}
	return (token);
}
*/

/*
void	*parser_parse_word(t_token *token, t_cmd *cmd)
{
	t_list	*node;
	t_token	*new_token;

	if (cmd->exec == NULL)
		cmd->exec = token;
	else
	{
		new_token = tokens_clone(*token);
		if (new_token == NULL)
		{
//			ft_lstclear(&cmd->args, token_free_node);
			return (NULL);
		}
		node = ft_lstnew(new_token);
		if (node == NULL)
		{
			free (new_token);
//			ft_lstclear(&cmd->args, token_free_node);
			return (NULL);
		}
		ft_lstadd_back(&cmd->args, node);
	}
	return (token);
}
*/