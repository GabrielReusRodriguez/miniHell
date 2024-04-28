/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:07:36 by gabriel           #+#    #+#             */
/*   Updated: 2024/04/29 00:10:00 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

bool	tokens_is_redir(t_token token)
{
	if (token.type == TOKEN_TYPE_RED_APPEND || \
		token.type == TOKEN_TYPE_RED_HERE_DOC || \
		token.type == TOKEN_TYPE_RED_TRUNCATE || \
		token.type == TOKEN_TYPE_RED_INPUT)
			return (true);
	return (false);
}

bool	tokens_is_parenthesis(t_token token)
{
	if (token.type == TOKEN_TYPE_PAR_OPEN || \
			token.type == TOKEN_TYPE_PAR_CLOSE)
			return (true);
	return (false);
}