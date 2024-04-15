/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:30:46 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/15 17:59:49 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENVIRONMENT_H
# define FT_ENVIRONMENT_H

# include "ft_datatypes.h"
# include "libft.h"


typedef	struct s_env_var
{
	t_string	var;
	t_string	value;
}	t_env_var;

typedef struct s_environment
{
	t_env_var	*vars;
	t_string	env;
}	t_environment;

t_env_var	ft_env_getenvvar(t_string var_name);
t_list      *ft_env_init(t_string *env);
void        ft_env_destroy(t_list *new_environment);
void        ft_env_freevar(void *arg);


#endif