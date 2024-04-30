/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:30:46 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/30 20:17:56 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "datatypes.h"
# include "libft.h"

typedef struct s_env_var
{
	t_string	var;
	t_string	value;
}	t_env_var;

typedef struct s_environment
{
	t_list		*vars;
	t_string	*env;
}	t_environment;

t_env_var	env_getenvvar(t_string var_name);
t_list		*env_init(t_string *env);
void		env_destroy(t_environment *environment);
void		env_freevar(void *arg);
t_string	*env_tostring(t_environment env);

/*
	exportar a char** 

*/

#endif
