/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:26:11 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/31 00:06:28 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "environment.h"
#include "libft.h"
#include "ptr.h"
#include "var.h"

/*
	We get the var struct with name var_name.
*/
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

/*
	We update the var of the list with the values of new_var.
	We DO NOT replace pointers.
*/
void	*env_update_var(t_list *node, t_var new_var)
{
	t_var		*var;
	t_string	aux;

	var = (t_var *)node->content;
	aux = var->value;
	var->value = ft_strdup(new_var.value);
	ptr_check_malloc_return(var->value, "Error at memory malloc.\n");
	free (aux);
	if (var->value == NULL)
		return (NULL);
	return (node);
}

/*
	We add new variable to the list.
	We clone the var with a new malloc .
*/
void	*env_add_var(t_environment *env, t_var var)
{
	t_list	*last_node;
	t_list	*new_node;
	t_var	*new_var;

	last_node = ft_lstlast(env->vars);
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

/*
	This function adds or updates a var depending if it 
	finds or not in the enviroment list.
*/
void	*env_addorupdate_var(t_environment *env, t_var var)
{
	t_list	*node;

	node = env_findvar(*env, var.key);
	if (node != NULL)
		return (env_update_var(node, var));
	else
		return (env_add_var(env, var));
}

/*
	We remove  the var with key from the list.
*/
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
