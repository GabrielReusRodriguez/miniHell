/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:47:03 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/08 23:14:17 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSOR_H
# define EXPANSOR_H

# include "environment.h"
# include "tokens.h"

/*
	expansor.c
*/
void		expansor_expand(t_environment *env, t_token *token);

/*
	expansor_vars.c
*/
size_t      expansor_vars_find_end_var(t_string str, size_t init);
t_string	expansor_vars_get_var(t_string str, size_t init, size_t *end_var, t_environment *env);
size_t	    expansor_vars_count_vars(t_string str);
t_string	*expansor_vars_create_chunks(t_string str);
t_string	expansor_vars_join_chunks(t_string *chunks);
void		expansor_vars_replace_vars(t_token *token, t_environment *env);


#endif