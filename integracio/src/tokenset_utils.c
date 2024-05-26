/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenset_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:28:42 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/25 18:26:04 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

void	tokens_destroy_tokenlist(t_token_set *list)
{
	ft_lstclear(&list->tokens, token_free_node);
	list->total = 0;
}

t_token_set	token_set_new(void)
{
	t_token_set	token_set;

	token_set.total = 0;
	token_set.tokens = NULL;
	token_set.last_read_token = NULL;
	return (token_set);
}

/*
	We have a token and we want to search the node of the list of tokens. 
	if it exists BEFORE last_node. 
	That is usefull to treat commands that are a sublist of tokens.
*/
t_list	*tokens_goto(t_list *token_list, t_token *token_searched, \
			t_list *last_node)
{
	t_list	*node;

	node = token_list;
	if (node == NULL)
		return (NULL);
	while (node != NULL && node->content != token_searched && node != last_node)
		node = node->next;
	if (node->content == token_searched)
		return (node);
	return (NULL);
}
