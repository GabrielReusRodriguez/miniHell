/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:35:06 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/15 18:00:29 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_environment.h"
#include "libft.h"

t_env_var	ft_env_getenvvar(t_string var_name)
{
	t_env_var	env;
	
	env.var = var_name;
	env.value = getenv(var_name);
	return (env);
}

static t_list	*ft_env_new_var(t_string str)
{
	t_list		*node;
	t_env_var	*env;
	int			initial_pos;
	int			size;		

	env = (t_env_var *)malloc(sizeof(t_env_var));
	if (env == NULL)
		return (NULL);
	size = ft_strlen(str);
	initial_pos = ft_istrchr(str, "=");
	if (initial_pos  < 0)
		return (ft_ptr_free(env));
	env->var = ft_substr(str, 0, initial_pos + 1);
	if (env->var == NULL)
		return (ft_ptr_free(env));
	env->value = ft_substr(str, initial_pos + 1 , size);
	if (env->value == NULL)
	{
		free (env->var);
		return (ft_ptr_free(env));
	}
	node = ft_lstnew(env);
	return (node);	
}

void	ft_env_freevar(void *arg)
{
	t_env_var	*var;

	var = (t_env_var *)arg;
	free(var->value);
	free(var->var);
}

t_list	*ft_env_init(t_string *env)
{
	t_list		*new_env;
	size_t		i;
	t_list		*node;
	
	i = 0;
	while (env[i] != NULL)
	{
		node = ft_env_new_var(env[i]);
		if (node == NULL)
		{
			ft_lstclear(&new_env, ft_env_freevar);
			return (NULL);
		}
		ft_lstadd_back(&new_env, node);
		i++;
	}
	return (new_env);
}
