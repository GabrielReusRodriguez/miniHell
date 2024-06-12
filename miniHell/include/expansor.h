/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:47:03 by greus-ro          #+#    #+#             */
/*   Updated: 2024/06/12 18:02:26 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSOR_H
# define EXPANSOR_H

# include "environment.h"
# include "minishell.h"
# include "tokens.h"

typedef struct s_expansor
{
	size_t		i;
	size_t		init;
	bool		is_quoted;
	t_string	str;
}	t_expansor;

/*
	expansor.c
*/
void		expansor_expand(t_environment *env, t_token *token);

/*
	expansor_vars.c
*/
size_t		expansor_vars_find_end_var(t_string str, size_t init);
t_string	expansor_vars_get_var(t_string str, size_t init, size_t *end_var, \
				t_minishell shell);
size_t		expansor_vars_count_vars(t_string str);
t_string	*expansor_vars_create_chunks(t_string str);
t_string	expansor_vars_join_chunks(t_string *chunks);

/*
	expansor_var2.c
*/

t_string	expansor_vars_treat_dollar(t_expansor *limits, \
				t_string expanded, t_minishell shell, t_token *next_t);
t_string	expansor_vars_treat_tilde(t_expansor *limits, \
				t_string expanded, t_minishell shell);

/*
	expansor_var3.c
*/
t_string	expansor_vars_join_acumulated(t_string acum, t_expansor limits);
void		expansor_vars_replace_vars(t_token *token, t_token *next_t, \
				t_minishell shell);
t_string	expansor_vars_replace_vars_init(t_expansor	*limits, \
				t_token token);

#endif