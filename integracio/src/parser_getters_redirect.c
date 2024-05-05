/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_getters_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:32:23 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/05 01:59:48 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"
#include "error_handler.h"
#include "redirect.h"

static void	*parser_parse_redir_in(t_list **list, t_list *node, t_list *end, t_cmd *cmd)
{
	t_token	*token;

	while (node != NULL && node != end)
	{
		token = (t_token *)node->content;
		if (tokens_isword(*token) == true)
		{
			cmd->red_in_origin = token;
			*list = node;
			return (node);
		}
		if (tokens_is_redir(*token) == true)
		{
			error_print("Syntax Error\n");
		   return (NULL);
		}
		node = node->next;
	}
	error_print("Syntax Error\n");
	return (NULL);
}

static void	*parser_parse_redir_out(t_list **list, t_list *node, t_list *end, t_cmd *cmd)
{
	t_token	*token;
	
	while (node != NULL && node != end)
	{
		token = (t_token *)node->content;
		if (tokens_isword(*token) == true)
		{
			cmd->red_out_dest = token;
			*list = node;
			return (node);
		}
		if (tokens_is_redir(*token) == true)
		{
			error_print("Syntax Error\n");	
		   return (NULL);
		}
		node = node->next;
	}
	error_print("Syntax Error\n");
	return (NULL);
}

void	*parser_parse_redir(t_list **list, t_list *end, t_cmd *cmd)
{
	t_token	*token;
	t_list	*node;

	node = (*list);
	token = (t_token *)(node->content);
	if (token->type == TOKEN_TYPE_RED_INPUT || \
			token->type == TOKEN_TYPE_RED_HERE_DOC)
	{
		cmd->red_in = token;
		node = node->next;
		return (parser_parse_redir_in(list, node, end, cmd));
	}
	if (token->type == TOKEN_TYPE_RED_APPEND || \
			token->type == TOKEN_TYPE_RED_TRUNCATE)
	{
		cmd->red_out = token;
		node = node->next;
		return (parser_parse_redir_out(list, node, end, cmd));
	}
	return (node);
}

//NEW VERSION***************************************

static void	*parser_parse_redir_in_v2(t_list **list, t_list *node, t_list *end)
{
	t_token		*token;

	while (node != NULL && node != end)
	{
		token = (t_token *)node->content;
		if (tokens_isword(*token) == true)
		{
			*list = node;
			return (token);
		}
		if (tokens_is_redir(*token) == true)
			return (error_print("Syntax Error\n"));
		node = node->next;
	}
	return (error_print("Syntax Error\n"));
}

static void	*parser_parse_redir_out_v2(t_list **list, t_list *node, t_list *end)
{
	t_token		*token;

	while (node != NULL && node != end)
	{
		token = (t_token *)node->content;
		if (tokens_isword(*token) == true)
		{
			*list = node;
			return (token);
		}
		if (tokens_is_redir(*token) == true)
			return (error_print("Syntax Error\n"));	
		node = node->next;
	}
	return (error_print("Syntax Error\n"));
}

#include <stdio.h>
void	*parser_parse_redir_v2(t_list **list, t_list *end, t_cmd *cmd)
{
	t_token		*token;
	t_list		*node;
	t_list		*new_node;
	t_redirect	*red;

	node = (*list);
	red = redirect_new();
	if (red == NULL)
		error_system_crash("Error at malloc\n");
	token = (t_token *)(node->content);
	red->type = token;
	if (token->type == TOKEN_TYPE_RED_INPUT || \
				token->type == TOKEN_TYPE_RED_HERE_DOC)
	{
		red->target = parser_parse_redir_in_v2(list, node->next, end);
		new_node = ft_lstnew(red);
		if (new_node == NULL)
			error_system_crash("Error in memory malloc\n");
		printf("token type %u _%s_\n", red->type->type, red->target->value);
		ft_lstadd_back(&cmd->redir_in, new_node);
	}
	if (token->type == TOKEN_TYPE_RED_APPEND || \
				token->type == TOKEN_TYPE_RED_TRUNCATE)
	{
		red->target = parser_parse_redir_out_v2(list, node->next, end);
		new_node = ft_lstnew(red);
		if (new_node == NULL)
			error_system_crash("Error in memory malloc\n");
		printf("token type %u _%s_\n", red->type->type, red->target->value);
		ft_lstadd_back(&cmd->redir_out, new_node);
	}
	return (node);
}

/*
void	*parser_parse_redir(t_list **list, t_list *end, t_cmd *cmd)
{
	t_token	*token;
	t_list	*node;

	node = (*list);
	token = (t_token *)(node->content);
	if (token->type == TOKEN_TYPE_RED_INPUT || \
			token->type == TOKEN_TYPE_RED_HERE_DOC)
	{
		cmd->red_in = token;
		node = node->next;
		while (node != NULL && node != end)
		{
			token = (t_token *)node->content;
			if (tokens_isword(*token) == true)
			{
				cmd->red_in_origin = token;
				*list = node;
				return (node);
			}
			node = node->next;
		}
		return (NULL);
	}
	if (token->type == TOKEN_TYPE_RED_APPEND || \
			token->type == TOKEN_TYPE_RED_TRUNCATE)
	{
		cmd->red_out = token;
		node = node->next;
		while (node != NULL && node != end)
		{
			token = (t_token *)node->content;
			if (tokens_isword(*token) == true)
			{
				cmd->red_out_dest = token;
				*list = node;
				return (node);
			}
			node = node->next;
		}
		return (NULL);
	}
	return (node);
}
*/