/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:26:11 by abluis-m          #+#    #+#             */
/*   Updated: 2024/06/01 00:44:23 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "environment.h"
#include "libft.h"
#include "ptr.h"
#include "var.h"
#include "minishell.h"

/*
	We find a var in the list of vars of the environmment.
*/
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

/*
	We count the number of vars
*/
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

/*
	We transform the list of vars to a char**
	it is used to pass the char ** to execve.
*/
t_string	*env_to_vector(t_environment env)
{
	t_string	*str_env;
	size_t		i;
	t_list		*node;
	t_string	aux;

	i = env_count_num_vars(env);
	str_env = ptr_new_matrix(i);
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
