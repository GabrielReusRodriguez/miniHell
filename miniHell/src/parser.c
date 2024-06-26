/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:43:57 by greus-ro          #+#    #+#             */
/*   Updated: 2024/06/01 02:23:10 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "datatypes.h"
#include "tokens.h"
#include "cmd.h"
#include "parser.h"
#include "expansor.h"
#include "error_handler.h"
#include "minishell.h"

/*
BASH Grammar
https://cmdse.github.io/pages/appendix/bash-grammar.html
*/
void	*parser_get_cmdset(t_token_set *token_set, t_cmd_set *cmd_set)
{
	t_cmd		cmd;
	size_t		i;

	*cmd_set = cmd_create_set(*token_set);
	if (cmd_set->cmds == NULL)
		return (NULL);
	i = 0;
	while (i < cmd_set->cmd_count)
	{
		if (parser_get_next_cmd(token_set, &cmd) == NULL)
		{
			cmd_destroy_set(cmd_set);
			cmd_destroy(&cmd);
			return (error_print("Error getting the commands.\n"));
		}
		if (cmd_isvalid(cmd) == false)
		{
			cmd_destroy_set(cmd_set);
			cmd_destroy(&cmd);
			return (error_print("Syntax error at command.\n"));
		}
		cmd_set->cmds[i] = cmd;
		i++;
	}
	return (cmd_set);
}

size_t	parser_count_cmds(t_token_set token_set)
{
	t_token	*token;
	size_t	cmd_count;
	t_list	*node;

	if (token_set.tokens == NULL)
		return (0);
	cmd_count = 0;
	node = token_set.tokens;
	while (node != NULL)
	{
		token = (t_token *)node->content;
		if (token->type == TOKEN_TYPE_AND || \
				token->type == TOKEN_TYPE_SEMICOLON || \
				token->type == TOKEN_TYPE_PIPE)
			cmd_count++;
		node = node->next;
	}
	return (cmd_count + 1);
}

void	*parser_get_next_cmd(t_token_set *token_set, t_cmd *cmd)
{
	t_list	*node;
	t_token	*token;
	t_list	*first_token;
	t_list	*last_token;

	last_token = NULL;
	if (token_set->last_read_token == NULL)
		node = token_set->tokens;
	else
		node = token_set->last_read_token->next;
	first_token = node;
	while (node != NULL)
	{
		token_set->last_read_token = node;
		token = (t_token *)node->content;
		if (parser_iscmdseparator(*token) == true)
		{
			last_token = node;
			break ;
		}
		node = node->next;
	}
	return (parser_create_cmd(first_token, last_token, cmd));
}

void	*parser_create_cmd(t_list *first_token, t_list *last_token, t_cmd *cmd)
{
	t_list	*node;
	t_token	*token;

	node = first_token;
	*cmd = cmd_new();
	while (node != NULL && node != last_token)
	{
		token = (t_token *)node->content;
		if (tokens_isredir(*token) == true)
			if (parser_parse_redir(&node, last_token, cmd) == NULL)
				return (NULL);
		if (tokens_isword(*token) == true)
			if (parser_parse_word(&node, cmd) == NULL)
				return (NULL);
		if (node != NULL && ((t_token *)node->content)->type != TOKEN_TYPE_PIPE)
			node = node->next;
	}
	return (cmd);
}
