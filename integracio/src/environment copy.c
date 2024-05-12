/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:26:11 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/12 23:26:42 by greus-ro         ###   ########.fr       */
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

/*
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
*/

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

size_t	env_count_num_vars(t_environment env)
{
	size_t	num_vars;
	t_list	*node;

	num_vars = 0;
	node = env.vars;
	while (node != NULL)
	{
		num_vars++;
		node = node->next;
	}
	return (num_vars);
}

t_string	*env_to_string(t_environment env)
{
	t_string	*str_env;
	size_t		i;
	t_list		*node;
	t_string	aux;

	i = env_count_num_vars(env);
	str_env = ptr_new_matrix(i);
	if (str_env == NULL)
		return (NULL);
	node = env.vars;
	i = 0;
	while (node != NULL)
	{
		aux = var_2_string(*(t_var *)(node->content));
		if (aux == NULL)
			return (ptr_freematrix(str_env));
		str_env[i++] = aux;
		node = node->next;
	}
	str_env[i] = NULL;
	return (str_env);
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

t_list	*env_findvar(t_environment env, t_string var_name)
{
	t_var	*var;
	t_list	*node;

	node = env.vars;
	while (node != NULL)
	{
		var = (t_var *)node->content;
		if (ft_strcmp(var_name, var->key) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

t_var	*env_get_var(t_environment env, t_string var_name)
{
	t_var	*var;
	t_list	*node;

	node = env_findvar(env, var_name);
	if (node == NULL)
		return (NULL);
	var = (t_var *)node->content;
	return (var);
}

void	*env_update_var(t_list *node, t_var new_var)
{
	t_var		*var;
	t_string	aux;

	var = (t_var *)node->content;
	aux = var->value;
	var->value = ft_strdup(new_var.value);
	free (aux);
	if (var->value == NULL)
		return (NULL);
	return (node);
}

void	*env_add_var(t_environment *env, t_var var)
{
	t_list	*last_node;
	t_list	*new_node;
	t_var	*new_var;

	last_node = list_getlast(env->vars);
	new_var = var_clone(var);
	if (new_var == NULL)
		return (NULL);
	new_node = ft_lstnew(new_var);
	if (new_node == NULL)
	{
		var_destroy(new_var);
		free (new_var);
		return (NULL);
	}
	ft_lstadd_back(&last_node, new_node);
	return (env);
}

void	*env_addorupdate_var(t_environment *env, t_var var)
{
	t_list	*node;

	node = env_findvar(*env, var.key);
	if (node != NULL)
		return (env_update_var(node, var));
	else
		return (env_add_var(env, var));
}

void	*env_remove_var(t_environment *env, t_string key)
{
	t_list	*node;
	t_list	*prev_node;
	t_var	*var;

	prev_node = NULL;
	node = env->vars;
	while (node != NULL)
	{
		var = (t_var *)node->content;
		if (ft_strcmp(key, var->key) == 0)
		{
			if (node == env->vars)
				env->vars = node->next;
			else
				prev_node->next = node->next;
			ft_lstdelone(node, env_del_varnode);
			return (key);
		}
		prev_node = node;
		node = node->next;
	}
	return (key);
}
