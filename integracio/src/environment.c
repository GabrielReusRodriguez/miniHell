/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:26:11 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/12 23:42:14 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "environment.h"
#include "libft.h"
#include "list_utils.h"
#include "ptr.h"
#include "var.h"

t_list	*env_new_varnode(t_string str)
{
	t_list		*node;
	t_var		*env_var;

	env_var = (t_var *)malloc(sizeof(t_var));
	if (env_var == NULL)
		return (NULL);
	if (var_init(str, env_var) == NULL)
	{
		var_destroy(env_var);
		free(env_var);
		return (NULL);
	}
	node = ft_lstnew(env_var);
	if (node == NULL)
	{
		var_destroy(env_var);
		free (env_var);
	}
	return (node);
}

void	env_del_varnode(void *arg)
{
	t_var	*var;

	var = (t_var *)arg;
	var_destroy(var);
	free (arg);
}

t_environment	env_create(void)
{
	t_environment	env;

	env.vars = NULL;
	return (env);
}

void	env_destroy(t_environment *env)
{
	ft_lstclear(&env->vars, env_del_varnode);
}

void	*env_init(t_environment *env, t_string *str_env)
{
	t_list		*new_list_env;
	size_t		i;
	t_list		*node;

	if (env == NULL)
		return (NULL);
	new_list_env = NULL;
	i = 0;
	while (str_env[i] != NULL)
	{
		node = env_new_varnode(str_env[i]);
		if (node == NULL)
		{
			ft_lstclear(&new_list_env, env_del_varnode);
			return (NULL);
		}
		ft_lstadd_back(&new_list_env, node);
		i++;
	}
	env->vars = new_list_env;
	return (str_env);
}
