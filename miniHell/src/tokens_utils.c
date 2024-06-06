/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:28:42 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/31 00:19:59 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "error_handler.h"
#include "ptr.h"

t_token	*token_new(int type, t_string value)
{
	t_token	*token;

	token = (t_token *)safe_malloc(sizeof (t_token));
	token->type = type;
	token->value = value;
	return (token);
}

void	*token_free(t_token *token)
{
	if (token != NULL)
	{
		if (token->value != NULL)
			free (token->value);
		free (token);
	}
	return (NULL);
}

void	token_free_node(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	if (token != NULL)
	{
		if (token->value != NULL)
			free (token->value);
		free (token);
	}
}
