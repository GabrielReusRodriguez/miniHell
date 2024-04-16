/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:30:46 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/16 09:24:31 by greus-ro         ###   ########.fr       */
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
	t_list		*vars;
	t_string	*env;
}	t_environment;

t_env_var	ft_env_getenvvar(t_string var_name);
t_list      *ft_env_init(t_string *env);
void        ft_env_destroy(t_environment *environment);
void        ft_env_freevar(void *arg);
t_string	*ft_env_tostring(t_environment env);


#endif