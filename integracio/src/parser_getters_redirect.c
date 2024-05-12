/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_getters_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:32:23 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/12 22:55:56 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"
#include "error_handler.h"
#include "redirect.h"
#include "ptr.h"

//NEW VERSION***************************************

static t_token	*parser_jump_spaces(t_list **node, t_list *end)
{
	t_token		*token;

	token = (t_token *)(*node)->content;
	while (*node != NULL && *node != end && token->type == TOKEN_TYPE_SPACE)
	{
		*node = (*node)->next;
		if (*node != NULL)
			token = (*node)->content;
	}
	return (token);
}

static void	*parser_parse_redir_inout(t_list **list, t_list *node, t_list *end)
{
	t_token		*token;
	t_string	value;
	t_string	aux;

	if (node == NULL)
		return (NULL);
	token = parser_jump_spaces(&node, end);
	if (node == NULL || node == end || tokens_isredir(*token))
		return (error_print("Syntax Error\n"));
	value = ft_strdup("");
	if (value == NULL)
		error_system_crash("Error at memory malloc\n");
	while (node != NULL && tokens_isword(*token))
	{
		aux = value;
		value = ft_strjoin(value, token->value);
		if (value == NULL)
			error_system_crash("Error at memory malloc\n");
		free (aux);
		node = node->next;
		if (node != NULL)
			token = node->content;
	}
	*list = node;
	return (token_new(TOKEN_TYPE_WORD, value));
}

static void	parser_parse_redir_push_red(t_redirect *red, t_token *token, \
				t_cmd *cmd)
{
	t_list	*new_node;

	new_node = ft_lstnew(red);
	if (new_node == NULL)
		error_system_crash("Error in memory malloc\n");
	if (tokens_isredir_in(*token) == true)
		ft_lstadd_back(&cmd->redir_out, new_node);
	else
		ft_lstadd_back(&cmd->redir_in, new_node);
}

void	*parser_parse_redir(t_list **list, t_list *end, t_cmd *cmd)
{
	t_token		*token;
	t_list		*node;
	t_redirect	*red;

	node = (*list);
	red = redirect_new();
	if (red == NULL)
		error_system_crash("Error at malloc\n");
	token = (t_token *)(node->content);
	red->type = token;
	if (tokens_isredir(*token) == true)
	{
		red->target = parser_parse_redir_inout(list, node->next, end);
		if (red->target == NULL)
		{
			redirect_freenode(red);
			return (NULL);
		}
		parser_parse_redir_push_red(red, token, cmd);
	}
	return (node);
}

/*
static void	*parser_parse_redir_in(t_list **list, t_list *node, t_list *end)
{
	t_token		*token;
	t_string	value;
	t_string	aux;

	if (node == NULL)
		return (NULL);
	token = (t_token *)node->content;
	while (node != NULL && node != end && token->type == TOKEN_TYPE_SPACE)
	{
		node = node->next;
		if (node != NULL)
			token = node->content;
	}
	if (node == NULL || node == end || tokens_is_redir(*token))
		return (error_print("Syntax Error\n"));
	value = ft_strdup("");
	if (value == NULL)
		error_system_crash("Error at memory malloc\n");
	while (node != NULL && tokens_isword(*token))
	{
		aux = value;
		value = ft_strjoin(value, token->value);
		if (value == NULL)
			error_system_crash("Error at memory malloc\n");
		free (aux);
		node = node->next;
		if (node != NULL)
			token = node->content;
	}
	*list = node;
	return (token_new(TOKEN_TYPE_WORD, value));
}

static void	*parser_parse_redir_out(t_list **list, t_list *node, t_list *end)
{
	t_token		*token;
	t_string	value;
	t_string	aux;

	if (node == NULL)
		return (NULL);
	token = (t_token *)node->content;
	while (node != NULL && node != end && token->type == TOKEN_TYPE_SPACE)
	{
		node = node->next;
		if (node != NULL)
			token = node->content;
	}
	if (node == NULL || node == end || tokens_is_redir(*token))
		return (error_print("Syntax Error\n"));
	value = ft_strdup("");
	if (value == NULL)
		error_system_crash("Error at memory malloc\n");
	while (node != NULL && tokens_isword(*token))
	{
		aux = value;
		value = ft_strjoin(value, token->value);
		if (value == NULL)
			error_system_crash("Error at memory malloc\n");
		free (aux);
		node = node->next;
		if (node != NULL)
		{
			token = node->content;
		}
	}
	*list = node;
	return (token_new(TOKEN_TYPE_WORD, value));
}
*/
/*
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
		if (red->target == NULL)
		{
			redirect_freenode(red);
			return (NULL);
		}
		new_node = ft_lstnew(red);
		if (new_node == NULL)
			error_system_crash("Error in memory malloc\n");
		ft_lstadd_back(&cmd->redir_in, new_node);
	}
	if (token->type == TOKEN_TYPE_RED_APPEND || \
				token->type == TOKEN_TYPE_RED_TRUNCATE)
	{
		red->target = parser_parse_redir_out(list, node->next, end);
		if (red->target == NULL)
		{
			redirect_freenode(red);
			return (NULL);
		}
		new_node = ft_lstnew(red);
		if (new_node == NULL)
			error_system_crash("Error in memory malloc\n");
		ft_lstadd_back(&cmd->redir_out, new_node);
	}
	return (node);
}
*/

/*
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

*/