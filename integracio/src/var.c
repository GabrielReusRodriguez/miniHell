/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:31:43 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/05 02:32:16 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "var.h"
#include "ptr.h"

t_var	var_new (void)
{
	t_var	var;

	var.key = NULL;
	var.value = NULL;
	return (var);
}

/*
static t_list	*env_new_var(t_string str)
{
	t_list		*node;
	t_var	*env;
	int			initial_pos;
	int			size;		

	env = (t_var *)malloc(sizeof(t_var));
	if (env == NULL)
		return (NULL);
	size = ft_strlen(str);
	initial_pos = ft_istrchr(str, "=");
	if (initial_pos < 0)
		return (ptr_free(env));
	env->key= ft_substr(str, 0, initial_pos);
	if (env->key == NULL)
		return (ptr_free(env));
	env->value = ft_substr(str, initial_pos + 1, size);
	if (env->value == NULL)
	{
		free (env->key);
		return (ptr_free(env));
	}
	node = ft_lstnew(env);
	return (node);
}
*/
t_var	*var_init(t_string str, t_var *var)
{
	size_t	size;
	int		initial_pos;
	
	size = ft_strlen(str);
	initial_pos = ft_istrchr(str, "=");
	if (initial_pos < 0)
		return (NULL);
	var->key= ft_substr(str, 0, initial_pos);
	if (var->key == NULL)
		return (NULL);
	var->value = ft_substr(str, initial_pos + 1, size);
	if (var->value == NULL)
	{
        var_destroy(var);
		//free (var->key);
		return (NULL);
	}
    return (var);
}

t_var	*var_clone(t_var var)
{
	t_var	*new_var;
	
	new_var	= (t_var *)malloc(sizeof(t_var));
	if (new_var == NULL)
		return (NULL);
	new_var->key = ft_strdup(var.key);
	if (new_var->key == NULL)
		return (ptr_free(new_var));
	new_var->value = ft_strdup(var.value);
	if (new_var->value == NULL)
	{
		free (new_var->key);
		free (new_var);
		return (NULL);
	}
	return (new_var);
}

t_string	var_2_string(t_var var)
{
	t_string	str;
	t_string	aux;

	aux = ft_strjoin(var.key, "=");
	if (aux == NULL)
		return (NULL);
	str = ft_strjoin(aux, var.value);
	free (aux);
	return (str);
}

void	var_destroy(t_var	*var)
{
	if (var == NULL)
		return ;
	if (var->value != NULL)
	{
		free(var->value);
		var->value = NULL;
	}
	if (var->key != NULL)
	{
		free(var->key);
		var->key = NULL;
	}
}

t_var	var_getenvvar(t_string var_name)
{
	t_var	env;

	env.key = var_name;
	env.value = getenv(var_name);
	return (env);
}
