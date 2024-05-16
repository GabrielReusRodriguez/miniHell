/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:31:43 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/16 22:10:37 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "var.h"
#include "ptr.h"
#include "expansor.h"

t_var	var_new(void)
{
	t_var	var;

	var.key = NULL;
	var.value = NULL;
	return (var);
}

t_var	*var_init(t_string str, t_var *var)
{
	size_t	size;
	int		initial_pos;

	size = ft_strlen(str);
	initial_pos = ft_istrchr(str, "=");
	if (initial_pos < 0)
		return (NULL);
	var->key = ft_substr(str, 0, initial_pos);
	if (var->key == NULL)
		return (NULL);
	if (var_has_valid_name(var->key) == false)
	{
		var_destroy(var);
		return (NULL);		
	}
	var->value = ft_substr(str, initial_pos + 1, size);
	if (var->value == NULL)
	{
		var_destroy(var);
		return (NULL);
	}
	return (var);
}

t_var	*var_clone(t_var var)
{
	t_var	*new_var;

	new_var = (t_var *)malloc(sizeof (t_var));
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
