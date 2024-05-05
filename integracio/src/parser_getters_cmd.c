/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_getters_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:35:39 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/05 01:21:06 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "cmd.h"

void	*parser_parse_word(t_token *token, t_cmd *cmd)
{
	t_list	*node;
	t_token	*new_token;

	if (cmd->exec == NULL)
		cmd->exec = token;
	else
	{
		new_token = tokens_clone(*token);
		if (new_token == NULL)
		{
//			ft_lstclear(&cmd->args, token_free_node);
			return (NULL);
		}
		node = ft_lstnew(new_token);
		if (node == NULL)
		{
			free (new_token);
//			ft_lstclear(&cmd->args, token_free_node);
			return (NULL);
		}
		ft_lstadd_back(&cmd->args, node);
	}
	return (token);
}
