/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_getters_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:35:39 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/22 22:39:21 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "cmd.h"
#include "error_handler.h"
#include "ptr.h"

static	t_string	parser_parse_word_get_value(t_list **token_list)
{
	t_string	value;
	t_token		*token;
	t_string	aux;

	value = ft_strdup("");
    ptr_check_malloc_return(value, "Error in memory malloc.\n");
	token = (*token_list)->content;
	while (*token_list != NULL && tokens_isword(*token) == true)
	{
		aux = value;
		value = ft_strjoin(value, token->value);
        ptr_check_malloc_return(value, "Error at memoruy malloc.\n");
		free (aux);
		*token_list = (*token_list)->next;
		if (*token_list != NULL)
			token = (*token_list)->content;
	}
	return (value);
}

void	*parser_parse_word(t_list **token_list, t_cmd *cmd)
{
	t_list		*node;
	t_string	value;

	if (cmd->exec == NULL)
	{
		value = parser_parse_word_get_value(token_list);
		cmd->exec = token_new(TOKEN_TYPE_WORD, value);
	}
	else
	{
		value = parser_parse_word_get_value(token_list);
		node = tokenizer_new_token_node(TOKEN_TYPE_WORD, value);
		ft_lstadd_back(&cmd->args, node);
	}
	return (cmd);
}
