/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_getters_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:35:39 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/29 00:37:12 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include <stdio.h>


/*
	Esta función nos salta el redirect. list es el puntero al token de 
		rediredct < > << >> y nos devuelve el mismo puntero apuntando 
		al siguiente token que NO pertenece al redirect. Null en 
		caso que no hayan encontrado redirect mas palabra.

		NOTA:  los redirects son << lim  o << origen .
*/
void *parser_jump_redir(t_list **list, t_list *end)
{
	t_token	*token;
	t_list	*node;

	node = *list;
	while (node != NULL && node != end)
	{
		token = (t_token *)node->content;
		if (tokens_is_parenthesis(*token) == false)
		{
			if (tokens_isword(*token) == true)
				break ;
		}
		node = node->next;
	}
	if (node == NULL || node == end)
		return (NULL);
	*list = node->next;
	return (node);
}

#include <stdio.h>

t_token	*parser_get_exec(t_list *token_list, t_list *end_cmd)
{
	t_token *token;
	t_list	*node;

	node = token_list;
	if (node == NULL)
		return (NULL);
	token = (t_token *)node->content;
	if (tokens_isword(*token) == true)
		return (token);
	while (node != NULL && node != end_cmd)
	{
		token = (t_token *)node->content;
		if (tokens_isword(*token) == true)
			return (token);
		if (tokens_is_redir(*token) == true)
		{
				if (parser_jump_redir(&node, end_cmd) == NULL)
					return (NULL);
		}
		else
			node = node->next;		
	}
	return (NULL);
}

t_list	*parser_get_args(t_list *token_list_node, t_token *exec_tk,t_list *end_cmd)
{
	t_list		*args;
	t_list		*node;
	t_list		*exec_node;
	t_token		*token;
	t_token		*new_token;

	args = NULL;
	if (token_list_node == NULL || exec_tk == NULL)
		return (NULL);
	exec_node = tokens_goto(token_list_node, exec_tk, end_cmd);
	if (exec_node == NULL)
		return (NULL);
	exec_node = exec_node->next;
	while (exec_node != NULL && exec_node != end_cmd)
	{
		token = exec_node->content;
		if(tokens_isword(*token) == true)
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
		}
		else
		{
			if (tokens_is_redir(*token) == true)
				break;	
		}
		exec_node = exec_node->next;
	}
	return (args);
/*

	token = token_list_node->content;

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
	*/
}

/*
t_list	*parser_get_args(t_list *token_list_node, t_token *exec_tk,t_list *end_cmd)
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
*/
/*
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
*/
