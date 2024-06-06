/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils_types.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:28:42 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/12 22:31:20 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

bool	tokens_isword(t_token token)
{
	if (token.type == TOKEN_TYPE_WORD || \
			token.type == TOKEN_TYPE_WORD_DQUOTE || \
			token.type == TOKEN_TYPE_WORD_SQUOTE)
		return (true);
	return (false);
}

bool	tokens_isredir_out(t_token token)
{
	if (token.type == TOKEN_TYPE_RED_APPEND || \
			token.type == TOKEN_TYPE_RED_TRUNCATE)
		return (true);
	return (false);
}

bool	tokens_isredir_in(t_token token)
{
	if (token.type == TOKEN_TYPE_RED_HERE_DOC || \
			token.type == TOKEN_TYPE_RED_INPUT)
		return (true);
	return (false);
}

bool	tokens_isredir(t_token token)
{
	if (token.type == TOKEN_TYPE_RED_APPEND || \
			token.type == TOKEN_TYPE_RED_HERE_DOC || \
			token.type == TOKEN_TYPE_RED_TRUNCATE || \
			token.type == TOKEN_TYPE_RED_INPUT)
		return (true);
	return (false);
}
