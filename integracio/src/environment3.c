/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:26:11 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/12 23:42:22 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "environment.h"
#include "libft.h"
#include "list_utils.h"
#include "ptr.h"
#include "var.h"

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