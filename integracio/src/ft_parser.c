/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:43:57 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/24 21:44:54 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "datatypes.h"
#include "tokens.h"

//TODO: WORK IN PROGRESS.....
/*
bool	ft_parser_isstopper(t_token token)
{
	if(token.type == TOKEN_TYPE_SEMICOLON || token.type == TOKEN_TYPE_PIPE || \
			token.type == TOKEN_TYPE_AND || token.type == TOKEN_TYPE_OR)
	{
		return (true);
	}
	return (false);
}
*/
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

t_token	*ft_parser_get_exec(t_list **token_list_node, t_list *end_cmd)
{
	t_token	*cmd_token;
	t_list	*node;

	cmd_token = (t_token *)(*token_list_node)->content;
	//Caso que empiece directamente por el comando.
	if (ft_tokens_isword(*cmd_token) == TRUE)
	{
		(*token_list_node) = (*token_list_node)->next;
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
		return (cmd_token);
	}
	return (NULL);
}

t_list	*ft_parser_get_args(t_list **token_list_node, t_list *end_cmd)
{
	t_list		*args;
	t_list		*node;
	t_token		*token;
	t_token		*new_token;

	args = NULL;
	token = ((*token_list_node)->content);
	while ((*token_list_node) != end_cmd && \
		(ft_tokens_isword(*token) == TRUE || \
		token->type == TOKEN_TYPE_PAR_OPEN || \
		token->type == TOKEN_TYPE_PAR_CLOSE ))
	{
		new_token = ft_tokens_clone(*token);
		node = ft_lstnew(new_token);
		if (node == NULL)
		{
			ft_lstclear(&args, ft_token_free);
			return (NULL);
		}
		ft_lstadd_back(&args, node);
		*token_list_node = (*token_list_node)->next;
	}
	return (args);
}

t_token *ft_parser_get_redir_input(t_list **token_list_node, t_list *end_cmd)
{
	t_token	*token;

	if (*token_list_node == end_cmd)
		return (NULL);
	token = (t_token *)(*token_list_node)->content;
	if (token->type == TOKEN_TYPE_RED_INPUT || \
			token->type == TOKEN_TYPE_RED_HERE_DOC)
	{
		token_list_node = (*token_list_node)->next;
		return (token);
	}
	return (NULL);
}

t_token	*ft_parser_get_redir_input_origin(t_list **token_list_node, \
				t_list *end_cmd)
{
	t_token	*token;

	if (*token_list_node == end_cmd)
		return (NULL);
	token = (t_token *)(*token_list_node)->content;
	(*token_list_node) = (*token_list_node)->next;
	return (token);
}

t_token	*ft_parser_get_redir_output(t_list **token_list_node, t_list *end_cmd)
{
	t_token	*token;

	if (*token_list_node == end_cmd)
		return (NULL);
	token = (t_token *)(*token_list_node)->content;
	(*token_list_node) = (*token_list_node)->next;
	return (token);
}

t_token	*ft_parser_get_redir_output_dest(t_list **token_list_node, \
			t_list *end_cmd)
{
	t_token	*token;

	if (*token_list_node == end_cmd)
		return (NULL);
	token = (t_token *)(*token_list_node)->content;
	(*token_list_node) = (*token_list_node)->next;
	return (token);
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
