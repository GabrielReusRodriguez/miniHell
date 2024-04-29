/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_getters_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:32:23 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/30 01:03:47 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"


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
