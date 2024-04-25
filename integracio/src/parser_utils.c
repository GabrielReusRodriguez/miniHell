/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:59:21 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/25 23:30:47 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

bool	parser_iscmdseparator(t_token token)
{
	if(token.type == TOKEN_TYPE_SEMICOLON || token.type == TOKEN_TYPE_PIPE || \
			token.type == TOKEN_TYPE_AND || token.type == TOKEN_TYPE_OR)
	{
		return (true);
	}
	return (false);
}