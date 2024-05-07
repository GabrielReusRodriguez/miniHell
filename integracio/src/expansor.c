/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:49:13 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/07 22:10:36 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "tokens.h"
#include "error_handler.h"

#include <stdio.h>

/*
void    expansor_expand(t_environment *env, t_token *token)
{
	size_t      i;
	t_string	aux;
	t_string	acum;
	t_string	chunk;

	i = 0;
	while(token->value[i] != '\0')
	{
		if (token->value[i] != '\'')
			chunk = expansor_treat_unexpand(i, token->value);
		else
			chunk = expansor_treat_expand(i, token->value, env);
		aux = acum;
		acum = ft_strjoin(aux, chunk);
		if (acum == NULL)
			error_system_crash("Error at memory malloc\n");
		free(aux);
		i++;
	}
	free(token->value);
	token->value = acum;
}
*/

static t_string    expansor_treat_squoted(size_t *i, t_string str)
{
	t_string    chunk;
	size_t      j;

	printf("SQUOTED expansor\n");
	j = 0;
	*i = *i + 1;
	while (str[*i + j] != '\0' && str[*i + j] != '\'')
		j++;
	if (str[*i + j] == '\0')
	{
		chunk = ft_substr(str, *i, j);
		if (chunk == NULL)
			error_system_crash("Error at memory malloc 1\n");
		*i = *i + j;
	}
	else
	{
		chunk = ft_substr(str, *i, j - 1);
		if (chunk == NULL)
			error_system_crash("Error at memory malloc 2\n");
		*i = *i + j + 1;		
	}
	return (chunk);
}

static t_string	expansor_treat_dquoted(size_t *i, t_string str, t_environment *env)
{
	t_string    chunk;
	size_t      j;

	printf("DQUOTED expansor\n");
	(void)env;
	j = 0;
	*i = *i + 1;
	while (str[*i + j] != '\0' && str[*i + j] != '\"')
		j++;
	if (str[*i + j] == '\0')
	{
		chunk = ft_substr(str, *i, j);
		if (chunk == NULL)
			error_system_crash("Error at memory malloc 3\n");
		*i = *i + j;
	}
	else
	{
		chunk = ft_substr(str, *i, j);
		if (chunk == NULL)
			error_system_crash("Error at memory malloc 4\n");
		*i = *i + j + 1;		
	}
	return (chunk);
}

static t_string	expansor_treat_normal(size_t *i, t_string str, t_environment *env)
{
	t_string    chunk;
	size_t      j;

	printf("NORMAL expansor\n");
	(void)env;
	j = 0;
	while (str[*i + j] != '\0' && str[*i + j] != '\"' && str[*i + j] != '\'')
		j++;
	printf("i %lu j %lu  _%d_\n",*i, j, str[*i + j]);
	if (str[*i + j] == '\0')
	{
		chunk = ft_substr(str, *i, j);
		if (chunk == NULL)
			error_system_crash("Error at memory malloc 5\n");
		*i = *i + j;
	}
	else
	{
		chunk = ft_substr(str, *i, j - 1);
		if (chunk == NULL)
			error_system_crash("Error at memory malloc 6\n");
		*i = *i + j;		
	}
	return (chunk);
}

static t_string	expansor_treat_expand(size_t *i, t_string str, t_environment *env)
{
	if (str[*i] == '\"')
		return (expansor_treat_dquoted(i, str, env));
	else
		return(expansor_treat_normal(i, str, env));
}

void    expansor_expand(t_environment *env, t_token *token)
{
	size_t      i;
	t_string	aux;
	t_string	acum;
	t_string	chunk;

	i = 0;
	acum = ft_strdup("");
	if (acum == NULL)
		error_system_crash("Error at memory malloc 7\n");	
	while(token->value[i] != '\0')
	{
		if (token->value[i] == '\'')
			chunk = expansor_treat_squoted(&i, token->value);
		else
			chunk = expansor_treat_expand(&i, token->value, env);
		aux = acum;
		acum = ft_strjoin(aux, chunk);
		if (acum == NULL)
			error_system_crash("Error at memory malloc 8\n");
		free(aux);
		free (chunk);
	}
	free(token->value);
	token->value = acum;
}
