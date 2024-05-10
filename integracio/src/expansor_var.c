/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:04:11 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/10 11:58:28 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"
#include "environment.h"
#include "error_handler.h"
#include "tokens.h"
#include "ptr.h"

#include <stdio.h>

size_t	expansor_vars_find_end_var(t_string str, size_t init)
{
	size_t	j;

	j = 1;
	//if (ft_isdigit(str[init + j]) == 1)
	if (ft_isdigit(str[init + j]) == 1 || str[init + j] == '\"' || str[init + j] == '\'')
		return (j);
//	while (str[init + j] != '\0' || str[init + j] != '\"')
	while (str[init + j] != '\0')
	{
		if (str[init + j] == '\"' || str[init + j] == '\'')
				return (j - 1);
		if (ft_isalnum(str[init + j]) == 0)
			break;
		j++;
	}
	return (j);
}

t_string	expansor_vars_get_var(t_string str, size_t init, size_t *end_var, t_environment *env)
{
	t_var		*var;
	t_string	var_key;
	t_string	var_value;
	
	*end_var = init + expansor_vars_find_end_var(str, init);
	var_key = ft_substr(str, init + 1, *end_var - init);
//	printf("\tVAR buscada : _%s_\n", var_key);
	if (var_key == NULL)
		error_system_crash("Error at memory malloc\n");	
	var = env_get_var(*env, var_key);
	if (var != NULL)
		var_value = ft_strdup(var->value);
	else
		var_value = ft_strdup("");
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
			continue;
		}
		if(replace_mode == true && str[i] == '$')
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
//	printf("Num chunks = %lu\n", num_chunks);
	chunks = (t_string *)malloc((num_chunks + 1)*sizeof(t_string));
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
//		printf("chunk: %s \n",chunks[i]);
		str_joined = ft_strjoin(str_joined, chunks[i]);
		if (str_joined == NULL)
			error_system_crash("ERROR at memory malloc\n");
		free (aux);
		i++;
	}
	return (str_joined);
}

void	expansor_vars_replace_vars(t_token *token, t_environment *env)
{
	t_string	*chunks;
	size_t		i;
	size_t		j;
	size_t		init;

	if (token->type == TOKEN_TYPE_WORD_SQUOTE)
		return ;
	chunks = expansor_vars_create_chunks(token->value);
	i = 0;
	init = i;
	j = 0;
	printf("TOKEN: _%s_\n",token->value);
	while (token->value[i] != '\0')
	{
		if (token->value[i] == '$')
		{
			if (init < i)
			{
				chunks[j] = ft_substr(token->value, init, i - init);
				if (chunks[j] == NULL)
					error_system_crash("Error at memory malloc\n");
				j++;
			}
			chunks[j++] = expansor_vars_get_var(token->value, i, &init, env);
			i = init;
		}
		else
			i++;
	}
	if (init < i)
	{
			chunks[j] = ft_substr(token->value, init, i - init);
//			printf("CHUNKS : i %lu init %lu %s \n", i, init, chunks[j]);
			if (chunks[j] == NULL)
				error_system_crash("Error at memory malloc\n");
	}
	free (token->value);
	token->value = expansor_vars_join_chunks(chunks);
	ptr_freematrix(chunks);
}
