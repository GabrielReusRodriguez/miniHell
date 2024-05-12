/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:16:58 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/12 23:51:47 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include <stddef.h>
# include "datatypes.h"
# include "libft.h"
# include "environment.h"
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
	TOKEN_TYPE_EMPTY,
	TOKEN_TYPE_SPACE
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
	tokenizer.c
*/
//t_token_set	tokenizer(t_string str);
t_token_set	tokenizer(t_string str, t_environment *env);
t_list		*tokenizer_get_next_token(t_string str, size_t *pos);
t_list		*tokenizer_new_word(t_string str, size_t *final_pos);
t_list		*tokenizer_new_pipe(size_t *i);
t_list		*tokenizer_new_semicolon(size_t *i);

/*
	tokenizer_quotes.c
*/
t_list		*tokenizer_new_dquote(t_string str, size_t *pos);
t_list		*tokenizer_new_squote(t_string str, size_t *pos);

/*
	tokenizer_redirect.c
*/
t_list		*tokenizer_new_redheredoc(size_t *i);
t_list		*tokenizer_new_redinput(size_t *i);
t_list		*tokenizer_new_redappend(size_t *i);
t_list		*tokenizer_new_redtruncate(size_t *i);

/*
	tokenizer_separators.c
*/
t_list		*tokenizer_new_semicolon(size_t *i);
t_list		*tokenizer_new_pipe(size_t *i);
bool		tokens_iscmdseparator(t_token token);

/*
	tokenizer_parenthesis.c
*/
t_list		*tokenizer_new_paropen(size_t *i);
t_list		*tokenizer_new_parclose(size_t *i);
bool		tokens_is_parenthesis(t_token token);

/*
	tokens_utils.c
*/
t_token_set	tokens_new(void);
void		token_free_node(void *ptr);
void		*token_free(t_token *ptr);
t_token		*tokens_clone(t_token token);

/*
	tokens_utils_types.c
*/
bool		tokens_isword(t_token token);
bool		tokens_isredir_out(t_token token);
bool		tokens_isredir_in(t_token token);
bool		tokens_isredir(t_token token);

/*
	tokenizer_utils.c
*/

void		*tokenizer_add_token(t_list *node, t_token_set *token_list);
bool		tokenizer_ischarclosed(t_string str, size_t pos, char quote);
bool		tokenizer_charinset(char c, t_string set);
bool		tokenizer_valida_str(t_string str);
t_list		*tokenizer_new_token_node(int type, t_string value);

/*
	tokenset_utils.c
*/
void		tokens_destroy_tokenlist(t_token_set *list);
t_list		*tokens_goto(t_list *token_list, t_token *token_searched, \
				t_list *last_node);
t_token_set	token_set_new(void);
t_token		*token_new(int type, t_string value);

/*
	tokenizer_words
*/
t_list		*tokenizer_new_word(t_string str, size_t *final_pos);

/*
	tokenizer_debug.c
*/
void		tokens_debug(t_token_set token_list);

#endif
