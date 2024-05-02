/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:30:46 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/02 21:00:57 by gabriel          ###   ########.fr       */
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
t_var	        env_getenvvar(t_string var_name);
void	        *env_init(t_environment *env, t_string *str_env);
void		    env_destroy(t_environment *environment);
//void		    env_freevar(void *arg);
t_string	    *env_tostring(t_environment env);
t_environment	env_create(void);

void			env_del_varnode(void *arg);
size_t			env_count_num_vars(t_environment env);
t_list	        *env_findvar(t_environment env, t_string var_name);
t_var           *env_get_var (t_environment env, t_string var_name);
void	        *env_update_var(t_list *node, t_var new_var);
void	        *env_add_var(t_environment *env, t_var var);
void	        *env_addorupdate_var(t_environment *env, t_var var);
void	        *env_remove_var(t_environment *env, t_string key);

#endif
