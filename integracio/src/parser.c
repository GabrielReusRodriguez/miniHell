/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:43:57 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/07 21:57:49 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "datatypes.h"
#include "tokens.h"
#include "cmd.h"
#include "parser.h"
#include "expansor.h"

/*
Chuleta gramaticas bash
https://cmdse.github.io/pages/appendix/bash-grammar.html
*/

void	*parser_get_cmdset(t_token_set *token_set, t_cmd_set	*cmd_set, t_environment *env)
{
	t_cmd		cmd;
	size_t		i;

	*cmd_set = cmd_create_set(*token_set);
	if (cmd_set->cmds == NULL)
		return (NULL);
	i = 0;
	while (i < cmd_set->cmd_count)
	{
		if (parser_get_next_cmd(token_set, &cmd, env) == NULL || \
				cmd_isvalid(cmd) == false)
		{
			cmd_destroy_set(cmd_set);
			return (NULL);
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

void	*parser_get_next_cmd(t_token_set *token_set, t_cmd *cmd, t_environment *env)
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
	return (parser_create_cmd(first_token, last_token, cmd, env));
}

void	*parser_create_cmd(t_list *first_token, t_list *last_token, t_cmd *cmd, t_environment *env)
{
	t_list	*node;
	t_token	*token;

	node = first_token;
	*cmd = cmd_new();
	while (node != NULL && node != last_token)
	{
		token = (t_token *)node->content;
		expansor_expand(env, token);
		if (tokens_is_redir(*token) == true)
			if (parser_parse_redir(&node, last_token, cmd) == NULL)
				return (NULL);
		if (tokens_isword(*token) == true)
			if (parser_parse_word(token, cmd) == NULL)
				return (NULL);
		node = node->next;
	}
	return (cmd);
}
