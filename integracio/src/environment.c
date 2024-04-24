/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:26:11 by abluis-m          #+#    #+#             */
/*   Updated: 2024/04/23 18:58:15 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "environment.h"
#include "libft.h"
#include "ptr.h"

t_env_var	env_getenvvar(t_string var_name)
{
	t_env_var	env;

	env.var = var_name;
	env.value = getenv(var_name);
	return (env);
}

static t_list	*env_new_var(t_string str)
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
	if (initial_pos < 0)
		return (ptr_free(env));
	env->var = ft_substr(str, 0, initial_pos);
	if (env->var == NULL)
		return (ptr_free(env));
	env->value = ft_substr(str, initial_pos + 1, size);
	if (env->value == NULL)
	{
		free (env->var);
		return (ptr_free(env));
	}
	node = ft_lstnew(env);
	return (node);
}

void	env_freevar(void *arg)
{
	t_env_var	*var;

	var = (t_env_var *)arg;
	free(var->value);
	free(var->var);
	free(var);
}

t_list	*env_init(t_string *env)
{
	t_list		*new_env;
	size_t		i;
	t_list		*node;

	new_env = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		node = env_new_var(env[i]);
		if (node == NULL)
		{
			ft_lstclear(&new_env, env_freevar);
			return (NULL);
		}
		ft_lstadd_back(&new_env, node);
		i++;
	}
	return (new_env);
}

void	env_destroy(t_environment *env)
{
	ft_lstclear(&env->vars, env_freevar);
}
