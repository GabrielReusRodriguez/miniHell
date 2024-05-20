/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:30:46 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/12 23:51:30 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "datatypes.h"
# include "libft.h"
# include "var.h"

typedef struct s_environment
{
	t_list		*vars;
}	t_environment;

/*
	environment.c
*/

t_list			*env_new_varnode(t_string str);
void			env_del_varnode(void *arg);
t_environment	env_create(void);
void			env_destroy(t_environment *env);
void			*env_init(t_environment *env, t_string *str_env);

/*
	environment2.c
*/
t_var			*env_get_var(t_environment env, t_string var_name);
void			*env_update_var(t_list *node, t_var new_var);
void			*env_add_var(t_environment *env, t_var var);
void			*env_addorupdate_var(t_environment *env, t_var var);
void			*env_remove_var(t_environment *env, t_string key);

/*
environment3.c
*/
t_list			*env_findvar(t_environment env, t_string var_name);
size_t			env_count_num_vars(t_environment env);
t_string		*env_to_vector(t_environment env);

void			env_debug(t_environment env);

#endif
