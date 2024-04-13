/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:51:25 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/11 19:05:06 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOKENS_H
# define FT_TOKENS_H

# include <stddef.h>
# include "ft_datatypes.h"
# include "libft.h"

/*
RED_TRUNCATE 	>
RED_APEND 		>>
RED_HERE_DOC 	<< 
RED_INPUT 		<
PAR_OPEN		(
PAR_CLOSE		)
*/

# define TOKEN_TYPE_UNKNOWN			0
# define TOKEN_TYPE_FILE 			1
# define TOKEN_TYPE_RED_TRUNCATE	2
# define TOKEN_TYPE_RED_APPEND		3
# define TOKEN_TYPE_RED_HERE_DOC	4
# define TOKEN_TYPE_RED_INPUT		5
# define TOKEN_TYPE_WORD			6
# define TOKEN_TYPE_PIPE			7
# define TOKEN_TYPE_AND				8
# define TOKEN_TYPE_OR				9
# define TOKEN_TYPE_PAR_OPEN		10
# define TOKEN_TYPE_PAR_CLOSE		11
# define TOKEN_TYPE_SEMICOLON		12
# define TOKEN_TYPE_EMPTY			13

typedef struct s_token
{
	t_uchar		type;
	t_string	value;	
}	t_token;

typedef struct s_token_set
{
	t_list		*tokens;
	size_t	total;
}	t_token_set;

t_token_set	ft_tokens_tokenize(t_string str);
t_token	ft_token_new(t_string str_token, int *i);

#endif