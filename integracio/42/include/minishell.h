/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:33:43 by abluis-m          #+#    #+#             */
/*   Updated: 2024/04/19 09:02:41 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Includes */
# include <stdbool.h>
# include "libft.h"

/* Defines*/
# define MINISHELL_PROMPT "minishell> "

# define SIGNAL_MODE_INTERACTIVE 0
# define SIGNAL_MODE_DEFAULT 2
# define SIGNAL_MODE_NOOP 3

# define PARSER_SEPARATORS  " \t\v\n"

/* Data types definitions*/

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

typedef struct s_token
{
	unsigned char	type;
	char			*value;	
}	t_token;

typedef struct s_token_set
{
	t_list		*tokens;
	size_t		total;
}	t_token_set;

/* Functions */

/* Signal */
void		signal_set_mode(int mode);

/* Parser */
bool		parser_charinset(char c, char *set);

/* Tokens */
t_token_set	tokens_tokenize(char *str);
t_token		token_new(char *str_token, int *i);
void		token_destroy_tokenset(t_token_set *list);
t_list		*token_get_next_token(char *str, size_t *pos);
t_list		*token_new_word(char *str, size_t *final_pos);
t_list		*token_new_pipe(size_t *i);
t_list		*token_new_semicolon(size_t *i);
/*
Parenthesis, not used... still....
t_list  	*token_new_paropen(size_t *i);
t_list  	*token_new_parclose(size_t *i);
*/
t_list		*token_new_redtruncate(size_t *i);
t_list		*token_new_redappend(size_t *i);
t_list		*token_new_redinput(size_t *i);
t_list		*token_new_redheredoc(size_t *i);
t_list		*token_new_squote(char *str, size_t *pos);
t_list		*token_new_dquote(char *str, size_t *pos);

/* TO DELETE */
void		ft_token_debug(t_token_set tokens);

#endif
