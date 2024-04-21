/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:51:25 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/21 23:10:34 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TOKENS_H
# define FT_TOKENS_H

# include <stddef.h>
# include "ft_datatypes.h"
# include "libft.h"
# include "ft_cmd.h"

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

# define TOKENS_SEPARATORS  " \t\v\n"

typedef struct s_token
{
	t_uchar		type;
	t_string	value;
}	t_token;

typedef struct s_token_set
{
	t_list		*tokens;
	t_list		*last_read_token;
	size_t      total;
}	t_token_set;

t_token_set	ft_tokenizer(t_string str);
t_token_set	ft_tokens_new(t_string str_token, int *i);
void		ft_tokens_destroy_tokenlist(t_token_set *list);
t_bool		ft_tokenizer_charinset(char c, t_string set);
t_bool		ft_tokens_isword(t_token token);
t_token     *ft_tokens_clone(t_token token);
void		ft_token_free(void *ptr);


#endif