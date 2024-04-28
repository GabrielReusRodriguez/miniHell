/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_getters_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:35:39 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/27 12:51:12 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdio.h>

t_token	*parser_get_exec(t_list **token_list_node, t_list *end_cmd)
{
	t_token	*cmd_token;
	t_list	*node;

	(void)end_cmd;
	if (token_list_node == NULL || *token_list_node == NULL)
		return (NULL);
	cmd_token = (t_token *)(*token_list_node)->content;
	//Caso que empiece directamente por el comando.
	if (tokens_isword(*cmd_token) == true)
	{
		*token_list_node = (*token_list_node)->next;
		return (cmd_token);
	}
	//Caso que empiece por parantesis abierto. Habra 
	//  que hacer un while para que salte
	//	todos los parentesis abiertos /cerrados -> ((  o  () 
	if (cmd_token->type == TOKEN_TYPE_PAR_OPEN)
	{
		node = (*token_list_node)->next;
		cmd_token = (t_token *)node->content;
		(*token_list_node) = (*token_list_node)->next;
		(*token_list_node) = (*token_list_node)->next;
		return (cmd_token);
	}
	return (NULL);
}

/*
	while (((*token_list_node) != NULL) && \
		(*token_list_node) != end_cmd && \
		(tokens_isword(*token) == true || \
		token->type == TOKEN_TYPE_PAR_OPEN || \
		token->type == TOKEN_TYPE_PAR_CLOSE))
*/
t_list	*parser_get_args(t_list **token_list_node, t_list *end_cmd)
{
	t_list		*args;
	t_list		*node;
	t_token		*token;
	t_token		*new_token;

	args = NULL;
	if (token_list_node == NULL || *token_list_node == NULL)
		return (NULL);
	token = ((*token_list_node)->content);
	printf("token type == %d \n", token->type);
	if (token->type == TOKEN_TYPE_PAR_OPEN)
	{
		node = (*token_list_node)->next;
		token = (t_token *)node->content;
		(*token_list_node) = (*token_list_node)->next;
	}
	while (((*token_list_node) != NULL) && \
		(*token_list_node) != end_cmd && \
		(tokens_isword(*token) == true))
	{
		new_token = tokens_clone(*token);
		if (new_token == NULL)
		{
			ft_lstclear(&args, token_free_node);
			return (NULL);
		}
		node = ft_lstnew(new_token);
		if (node == NULL)
		{
			ft_lstclear(&args, token_free_node);
			return (NULL);
		}
		ft_lstadd_back(&args, node);
		*token_list_node = (*token_list_node)->next;
		if (*token_list_node != NULL)
			token = ((*token_list_node)->content);
	}
	return (args);
}
