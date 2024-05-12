/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:04:11 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/12 23:10:02 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"
#include "environment.h"
#include "error_handler.h"
#include "tokens.h"
#include "ptr.h"
#include "expansor.h"

#include <stdio.h>

size_t	expansor_vars_find_end_var(t_string str, size_t init)
{
	size_t	j;

	j = 0;
	if (str[init + j] == '\0' || !(ft_isalpha(str[init + j]) || \
			tokenizer_charinset(str[init + j], "_")))
		return (0);
	while (ft_isalnum(str[init + j]) || tokenizer_charinset(str[init + j], "_"))
		j++;
	return (j);
}

t_string	expansor_vars_get_var(t_string str, size_t init, size_t *end_var, \
				t_environment *env)
{
	t_var		*var;
	t_string	var_key;
	t_string	var_value;
	size_t		size_var;

	size_var = expansor_vars_find_end_var(str, init);
	(*end_var) = init + size_var;
	if (size_var == 0)
	{
		var_value = ft_strdup("");
		ptr_check_malloc_return(var_value, "Error at memory malloc\n");
		return (var_value);
	}
	var_key = ft_substr(str, init, *end_var - init);
	ptr_check_malloc_return(var_key, "Error at memory malloc\n");
	var = env_get_var(*env, var_key);
	if (var != NULL)
		var_value = ft_strdup(var->value);
	else
		var_value = ft_strdup("");
	ptr_check_malloc_return(var_value, "Error at memory malloc\n");
	free (var_key);
	return (var_value);
}

size_t	expansor_vars_count_vars(t_string str)
{
	size_t	num;
	size_t	i;
	bool	replace_mode;

	num = 0;
	i = 0;
	replace_mode = true;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			replace_mode = !replace_mode;
			i++;
			continue ;
		}
		if (replace_mode == true && str[i] == '$')
			num++;
		i++;
	}
	return (num + 1);
}

t_string	*expansor_vars_create_chunks(t_string str)
{
	t_string	*chunks;
	size_t		num_chunks;
	size_t		i;

	num_chunks = expansor_vars_count_vars(str);
	chunks = (t_string *)malloc((num_chunks + 1) * sizeof(t_string));
	if (chunks == NULL)
		error_system_crash("Error at memory malloc\n");
	i = 0;
	while (i <= num_chunks)
	{
		chunks[i] = NULL;
		i++;
	}
	return (chunks);
}

t_string	expansor_vars_join_chunks(t_string *chunks)
{
	t_string	str_joined;
	t_string	aux;
	size_t		i;

	i = 0;
	str_joined = ft_strdup("");
	if (str_joined == NULL)
		error_system_crash("ERROR at memory malloc\n");
	while (chunks[i] != NULL)
	{
		aux = str_joined;
		str_joined = ft_strjoin(str_joined, chunks[i]);
		if (str_joined == NULL)
			error_system_crash("ERROR at memory malloc\n");
		free (aux);
		i++;
	}
	return (str_joined);
}
