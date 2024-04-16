/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:10:33 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/16 10:28:04 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_environment.h"
#include "ft_ptr.h"

static size_t	ft_env_count_vars(t_environment env)
{
	size_t	total;
	t_list	*node;

	total = 0;
	node = env.vars;
	while (node != NULL)
	{
		total++;
		node = node->next;
	}
	return (total);
}

t_string	ft_env_var2string(t_env_var *var)
{
	t_string	string;
	t_string	aux;
	
	aux = ft_strjoin(var->var, "=");
	if (aux == NULL)
		return (NULL);
	string = ft_strjoin(aux, var->value);
	free (aux);
	return (string);
}

t_string	*ft_env_tostring(t_environment env)
{
	t_string	*str_env;
	size_t		i;
	t_list		*node;
	size_t		total;

	total = ft_env_count_vars(env);
	str_env = (char **)malloc((total + 1) * sizeof(char *));
	if (str_env == NULL)
		return (NULL);
	node = env.vars;
	i = 0;
	while(node != NULL)
	{
		str_env[i] = ft_env_var2string((t_env_var *)node->content);
		if (str_env[i] == NULL)
		{
			ft_ptr_freematrix_wsize(str_env, i);
			return (NULL);
		}
		node = node->next;
		i++;
	}
	str_env[i] = NULL;
	return (str_env);
}