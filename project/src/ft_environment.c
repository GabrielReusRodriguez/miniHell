/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:35:06 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/10 20:55:15 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_environment.h"

t_env_var	ft_env_getenvvar(t_string var_name)
{
	t_env_var	env;
	
	env.var = var_name;
	env.value = getenv(var_name);
	return (env);
}
