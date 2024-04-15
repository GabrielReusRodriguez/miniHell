/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:51:25 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/15 17:16:43 by gabriel          ###   ########.fr       */
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

enum e_token_type
{
    TOKEN_TYPE_UNKNOWN,
    TOKEN_TYPE_FILE,
    TOKEN_TYPE_RED_TRUNCATE,
    TOKEN_TYPE_RED_APPEND,
    TOKEN_TYPE_RED_HERE_DOC,
    TOKEN_TYPE_RED_INPUT,
    TOKEN_TYPE_WORD,
    TOKEN_TYPE_WORD_SQUOTE,
    TOKEN_TYPE_WORD_DQUOTE,
    TOKEN_TYPE_PIPE,
    TOKEN_TYPE_AND,
    TOKEN_TYPE_OR,
    TOKEN_TYPE_PAR_OPEN,
    TOKEN_TYPE_PAR_CLOSE,
    TOKEN_TYPE_SEMICOLON,
    TOKEN_TYPE_EMPTY
};
/*
# define TOKEN_TYPE_UNKNOWN			99
# define TOKEN_TYPE_FILE 			1
# define TOKEN_TYPE_RED_TRUNCATE	2
# define TOKEN_TYPE_RED_APPEND		3
# define TOKEN_TYPE_RED_HERE_DOC	4
# define TOKEN_TYPE_RED_INPUT		5
# define TOKEN_TYPE_WORD			6
# define TOKEN_TYPE_WORD_SQUOTE		7
# define TOKEN_TYPE_WORD_DQUOTE		8
# define TOKEN_TYPE_PIPE			9
# define TOKEN_TYPE_AND				10
# define TOKEN_TYPE_OR				11
# define TOKEN_TYPE_PAR_OPEN		12
# define TOKEN_TYPE_PAR_CLOSE		13
# define TOKEN_TYPE_SEMICOLON		14
# define TOKEN_TYPE_EMPTY			15
*/

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
void	ft_token_destroy_tokenlist(t_token_set *list);


#endif