/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:26:11 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/23 18:24:38 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "environment.h"
#include "libft.h"
#include "ptr.h"
#include "var.h"

/*
	We create a new node of list of vars from the string a=b
*/
t_list	*env_new_varnode(t_string str)
{
	t_list		*node;
	t_var		*env_var;

	env_var = (t_var *)safe_malloc(sizeof(t_var));
	if (var_init(str, env_var) == NULL)
	{
		var_destroy(env_var);
		free(env_var);
		return (NULL);
	}
	node = ft_lstnew(env_var);
	ptr_check_malloc_return(node, "Error at memory malloc.\n");
	return (node);
}

/* 
	Function to use when we delete ALL the var list. ( from libft)
*/
void	env_del_varnode(void *arg)
{
	t_var	*var;

	var = (t_var *)arg;
	var_destroy(var);
	free (arg);
}

/*
	We create an enviroment.
*/
t_environment	env_create(void)
{
	t_environment	env;

	env.vars = NULL;
	return (env);
}

/*
	We clear the list of vars
*/
void	env_destroy(t_environment *env)
{
	ft_lstclear(&env->vars, env_del_varnode);
}

/*
	We init  the list of environemnt vars
	we  get a char ** var and we treat every string
	to get the variable.
*/
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
