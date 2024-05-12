/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:28:42 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/12 22:23:33 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "error_handler.h"

t_token	*token_new(int type, t_string value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof (t_token));
	if (token == NULL)
		error_system_crash("Error at memory malloc\n");
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

t_token	*tokens_clone(t_token token)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->type = token.type;
	new_token->value = ft_strdup(token.value);
	if (new_token->value == NULL)
		return (token_free(new_token));
	return (new_token);
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
