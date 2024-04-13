/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:30:46 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/10 20:55:30 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENVIRONMENT_H
# define FT_ENVIRONMENT_H

# include "ft_datatypes.h"

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

#endif