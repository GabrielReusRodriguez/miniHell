/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:16:58 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/23 23:37:39 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include <stddef.h>
# include "datatypes.h"
# include "libft.h"
//# include "ft_cmd.h"

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
	size_t		total;
}	t_token_set;

/*
t_token_set	ft_tokenizer(t_string str);
t_token_set	ft_tokens_new(t_string str_token, int *i);
void		ft_tokens_destroy_tokenlist(t_token_set *list);
bool		ft_tokenizer_charinset(char c, t_string set);
bool		ft_tokens_isword(t_token token);
t_token		*ft_tokens_clone(t_token token);
void		ft_token_free(void *ptr);
t_list		*ft_tokenizer_get_next_token(t_string str, size_t *pos);
t_list		*ft_tokenizer_new_pipe(size_t *i);
*/
/*
	tokenizer.c
*/
t_token_set	ft_tokenizer(t_string str);
t_list		*ft_tokenizer_get_next_token(t_string str, size_t *pos);
t_list		*ft_tokenizer_new_word(t_string str, size_t *final_pos);
t_list		*ft_tokenizer_new_pipe(size_t *i);
t_list		*ft_tokenizer_new_semicolon(size_t *i);

/*
	tokenizer_quotes.c
*/
t_list		*ft_tokenizer_new_dquote(t_string str, size_t *pos);
t_list		*ft_tokenizer_new_squote(t_string str, size_t *pos);

/*
	tokenizer_redirect.c
*/
t_list		*ft_tokenizer_new_redheredoc(size_t *i);
t_list		*ft_tokenizer_new_redinput(size_t *i);
t_list		*ft_tokenizer_new_redappend(size_t *i);
t_list		*ft_tokenizer_new_redtruncate(size_t *i);

/*
	tokenizer_separators.c
*/
t_list		*ft_tokenizer_new_semicolon(size_t *i);
t_list		*ft_tokenizer_new_pipe(size_t *i);
bool		ft_tokens_iscmdseparator(t_token token);

/*
	tokenizer_parenthesis.c
*/
t_list		*ft_tokenizer_new_paropen(size_t *i);
t_list		*ft_tokenizer_new_parclose(size_t *i);

/*
	tokens_utils.c
*/

t_token_set	ft_tokens_new(void);
void		ft_token_free(void *ptr);
bool		ft_tokens_isword(t_token token);
t_token		*ft_tokens_clone(t_token token);

/*
	tokenizer_utils.c
*/

bool		ft_tokens_isword(t_token token);
void		*ft_tokenizer_add_token(t_list *node, t_token_set *token_list);
bool		ft_tokenizer_ischarclosed(t_string str, size_t pos, char quote);
bool		ft_tokenizer_charinset(char c, t_string set);

/*
	tokenset_utils.c
*/
void		ft_tokens_destroy_tokenlist(t_token_set *list);
void		*ft_tokenizer_add_token(t_list *node, t_token_set *token_list);

void		ft_tokens_debug(t_token_set token_list);

#endif
