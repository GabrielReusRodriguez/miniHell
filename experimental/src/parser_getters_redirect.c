/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_getters_redirect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:32:23 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/31 00:13:21 by greus-ro         ###   ########.fr       */
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

static t_string	parser_parse_redir_inout_join(t_string value, \
					t_string token_value)
{
	t_string	aux;

	aux = ft_strjoin(value, token_value);
	ptr_check_malloc_return(aux, "Error at memory malloc\n");
	free (value);
	return (aux);
}

static void	*parser_parse_redir_inout(t_list **list, t_list *node, t_list *end)
{
	t_token		*token;
	t_string	value;
	t_uchar		token_type;

	if (node == NULL)
		return (NULL);
	token_type = TOKEN_TYPE_WORD_DQUOTE;
	token = parser_jump_spaces(&node, end);
	if (node == NULL || node == end || tokens_isredir(*token))
		return (error_print("Syntax Error\n"));
	value = ft_strdup("");
	ptr_check_malloc_return(value, "Error at memory malloc\n");
	while (node != NULL && tokens_isword(*token))
	{
		if (token->type != TOKEN_TYPE_WORD_DQUOTE)
			token_type = TOKEN_TYPE_WORD;
		value = parser_parse_redir_inout_join(value, token->value);
		node = node->next;
		if (node != NULL)
			token = node->content;
	}
	*list = node;
	return (token_new(token_type, value));
}

static void	parser_parse_redir_push_red(t_redirect *red, t_token *token, \
				t_cmd *cmd)
{
	t_list	*new_node;

	new_node = ft_lstnew(red);
	ptr_check_malloc_return(new_node, "Error in memory malloc.\n");
	if (tokens_isredir_in(*token) == true)
		ft_lstadd_back(&cmd->redir_in, new_node);
	else
		ft_lstadd_back(&cmd->redir_out, new_node);
}

void	*parser_parse_redir(t_list **list, t_list *end, t_cmd *cmd)
{
	t_token		*token;
	t_list		*node;
	t_redirect	*red;

	node = (*list);
	red = redirect_new();
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
