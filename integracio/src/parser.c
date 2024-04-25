/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:43:57 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/26 00:20:04 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "datatypes.h"
#include "tokens.h"
#include "cmd.h"
#include "parser.h"

#include <stdio.h>

void	*parser_get_cmds(t_token_set *token_set, t_cmd_set	*cmd_set)
{
	t_cmd		cmd;
	size_t		i;

	*cmd_set = cmd_create_set(*token_set);
	if (cmd_set->cmds == NULL)
		return (NULL);
	i = 0;
	while (i < cmd_set->num_cmds)
	{
		if (parser_get_next_cmd(token_set, &cmd) == NULL || cmd_isvalid(cmd) == false)
		{
			cmd_destroy_set(cmd_set);
			return (NULL);
		}
		cmd_set->cmds[i] = cmd;
		i++;
	}
	return (cmd_set);
}

size_t  parser_count_cmds(t_token_set token_set)
{
	t_token	*token;
	size_t	num_cmds;
	t_list	*node;

	if (token_set.tokens == NULL)
		return (0);
	num_cmds = 0;
	node = token_set.tokens;
	while (node != NULL)
	{
		token = (t_token *)node->content;
		if (token->type == TOKEN_TYPE_AND || \
				token->type == TOKEN_TYPE_SEMICOLON || \
				token->type == TOKEN_TYPE_PIPE )
			num_cmds++;
		node = node->next;
	}
	return (num_cmds + 1);
}

void	*parser_get_next_cmd(t_token_set *token_set, t_cmd *cmd)
{
	t_list	*node;
	t_token	*token;
	t_list	*first_token;
	t_list	*last_token;

	if (token_set->last_read_token == NULL)
		node = token_set->tokens;
	else
		node = token_set->last_read_token->next;
	first_token = node;
	while(node != NULL)
	{
		token_set->last_read_token = node;
		token = (t_token *)node->content;
		if (parser_iscmdseparator(*token) == true)
		{
			last_token = node;
			break;
		}
		node = node->next;
	}
	return (parse_create_cmd(first_token, last_token, cmd));
}

void	*parse_create_cmd(t_list *first_token, t_list *last_token, t_cmd *cmd)
{
	*cmd = cmd_new();
	cmd->red_in = parser_get_redir_input(&first_token, last_token);
	if (cmd->red_in != NULL)
		cmd->red_in_origin = parser_get_redir_input_origin(&first_token, \
								last_token);
	cmd->exec = parser_get_exec(&first_token, last_token);
	cmd->args = parser_get_args(&first_token, last_token);
	cmd->red_out = parser_get_redir_output(&first_token, last_token);
	if (cmd->red_out != NULL)
		cmd->red_out_dest = parser_get_redir_output_dest(&first_token, \
								last_token);
	return (cmd);
}


//TODO: WORK IN PROGRESS.....
/* Valido que
	tenga al menos una palabra
	no acabe en pipe.
*/
/*
bool  ft_parser_validate_tokenset(t_token_set token_set)
{
	t_list	*node;

	//TODO: pendiente implementar todas las validaciones.
	node = token_set.tokens;
	if (node == NULL)
		return (false);
	return (true);	
}

t_cmd	ft_parser_get_next_comand(t_token_set *token_set)
{
	t_list	*node;
	t_list	*command;
	t_token	*token;
	t_cmd	cmd;

	cmd = ft_cmd_new();
	if (token_set->last_read_token == NULL)
		node = token_set->tokens;
	else
		node = token_set->last_read_token->next;
	cmd.first_token = node;
	while(node != NULL)
	{
		token_set->last_read_token = node;
		token = (t_token *)node->content;
		if (ft_parser_iscmdseparator(*token) == TRUE)
			break;
		node = node->next;
	}
	cmd.last_token = node;
	return (cmd);
}

t_string	ft_parser_sublist_2_str(t_token *first, t_token *last)
{
	t_string	str_cmd;
	t_string	aux;
	t_list		*node;
	t_token		*token;

	str_cmd = ft_strdup("");
	node = first;
	while (node != NULL && node != last)
	{
		token = (t_token *)node->content;
		if (ft_parser_iscmdseparator(*token) == TRUE)
			break ;
		aux = str_cmd;
		str_cmd = ft_strjoin(aux, " ");
		free(aux);
		aux = str_cmd;
		str_cmd = ft_strjoin(aux, token->value);
		free (aux);
	}
	return (str_cmd);	
}

t_bool		ft_parser_has_morecmds(t_token_set token_set)
{
	if (token_set.last_read_token != NULL && \
			token_set.last_read_token->next == NULL)
		return (FALSE);
	return (TRUE);
}





t_token *ft_parser_get_stopper(t_list **token_list_node, t_list *end_cmd)
{
	t_list	*node;
	t_token	*token;
	
	node = *token_list_node;
	while (node != NULL && node != end_cmd)
	{
		if (ft_parser_isstopper(*token) == TRUE)
		{
			return (token);
		}
		(*token_list_node) = (*token_list_node)->next;
		node = (*token_list_node);
	}
	return (NULL);
}

t_cmd	ft_parser_get_next_comand(t_token_set *token_set)
{
	t_list	*node;
	t_list	*command;
	t_token	*token;
	t_cmd	cmd;

	cmd = ft_cmd_new();
	if (token_set->last_read_token == NULL)
		node = token_set->tokens;
	else
		node = token_set->last_read_token->next;
	cmd.first_token = node;
	while(node != NULL)
	{
		token_set->last_read_token = node;
		token = (t_token *)node->content;
		if (ft_parser_iscmdseparator(*token) == TRUE)
			break;
		node = node->next;
	}
	cmd.last_token = node;
	ft_cmd_parse_command(&cmd);
	return (cmd);
}

void	*ft_parser_parse_command(t_cmd *cmd)
{
	t_list  *token_node;

	token_node = cmd->first_token;
	cmd->red_in = ft_parser_get_redir_in(&token_node, cmd->last_token);
	if (cmd->red_in != NULL)
		cmd->red_in_origin = ft_parser_get_redir_input_origin(&token_node, \
				cmd->last_token);
	cmd->exec = ft_parser_get_exec(&token_node, cmd->last_token);
	cmd->args = ft_parser_get_args(&token_node, cmd->last_token);
	cmd->red_out = ft_parser_get_redir_output(&token_node, cmd->last_token);
	if (cmd->red_out != NULL)
		cmd->red_out_dest = ft_parser_get_redir_output_dest(&token_node, \
								cmd->last_token);
	return (NULL);
}
*/
