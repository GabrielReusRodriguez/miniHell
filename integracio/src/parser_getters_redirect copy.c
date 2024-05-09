/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_getters_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:32:23 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/05 18:54:12 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"
#include "error_handler.h"
#include "redirect.h"

//NEW VERSION***************************************

static void	*parser_parse_redir_in(t_list **list, t_list *node, t_list *end)
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

static void	*parser_parse_redir_out(t_list **list, t_list *node, t_list *end)
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

void	*parser_parse_redir(t_list **list, t_list *end, t_cmd *cmd)
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
		red->target = parser_parse_redir_in(list, node->next, end);
		new_node = ft_lstnew(red);
		if (new_node == NULL)
			error_system_crash("Error in memory malloc\n");
		ft_lstadd_back(&cmd->redir_in, new_node);
	}
	if (token->type == TOKEN_TYPE_RED_APPEND || \
				token->type == TOKEN_TYPE_RED_TRUNCATE)
	{
		red->target = parser_parse_redir_out(list, node->next, end);
		new_node = ft_lstnew(red);
		if (new_node == NULL)
			error_system_crash("Error in memory malloc\n");
		ft_lstadd_back(&cmd->redir_out, new_node);
	}
	return (node);
}
