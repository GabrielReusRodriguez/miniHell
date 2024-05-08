/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:49:13 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/09 00:41:18 by gabriel          ###   ########.fr       */
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
//	*i = *i + 1;
	while (str[*i + 1 + j] != '\0' && str[*i + 1 + j] != '\'')
		j++;
	if (str[*i + j + 1] == '\0')
	{
		chunk = ft_substr(str, *i, j + 1);
		if (chunk == NULL)
			error_system_crash("Error at memory malloc\n");
		*i = *i + j + 1;
	}
	else
	{
//		chunk = ft_substr(str, *i, j-1);
		chunk = ft_substr(str, *i, j + 1);
		if (chunk == NULL)
			error_system_crash("Error at memory malloc\n");
		*i = *i + j + 1;
		//*i = *i + j;		
	}
	printf("SALIDA squote: _%s_ \n",chunk);
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
			error_system_crash("Error at memory malloc\n");
		*i = *i + j;
	}
	else
	{
		chunk = ft_substr(str, *i, j);
		if (chunk == NULL)
			error_system_crash("Error at memory malloc\n");
		*i = *i + j + 1;		
	}
	return (chunk);
}

static t_string	expansor_treat_normal(size_t *i, t_string str, t_environment *env)
{
	t_string    chunk;
	size_t      j;

	(void)env;
	j = 0;
	while (str[*i + j] != '\0' && str[*i + j] != '\"' && str[*i + j] != '\'')
		j++;
	if (str[*i + j] == '\0')
	{
		chunk = ft_substr(str, *i, j);
		if (chunk == NULL)
			error_system_crash("Error at memory malloc\n");
		*i = *i + j;
	}
	else
	{
		chunk = ft_substr(str, *i, j - 1);
		if (chunk == NULL)
			error_system_crash("Error at memory malloc\n");
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
		error_system_crash("Error at memory malloc\n");	
	while(token->value[i] != '\0')
	{
		if (token->value[i] == '\'')
			chunk = expansor_treat_squoted(&i, token->value);
		else
			chunk = expansor_treat_expand(&i, token->value, env);
		aux = acum;
		acum = ft_strjoin(aux, chunk);
		if (acum == NULL)
			error_system_crash("Error at memory malloc\n");
		free(aux);
		free (chunk);
	}
	free(token->value);
	token->value = acum;
}

/*
t_string	expansor_replace_var_content(t_string *replaced, t_string str_var, t_environment *env)
{
	t_var		*var;
	t_string	aux;

	var = env_get_var(*env, str_var);
	if (var != NULL)
	{
		aux = *replaced;
		*replaced = ft_strjoin(*replaced, var->key);
		free (aux);
		if ( *replaced == NULL)
			error_system_crash("Error at strjoin\n");
	}
	return (*replaced);
}

t_string	expansor_replace_vars(t_string str, t_environment *env)
{
	t_string	replaced;
	t_string	before;
	size_t		i;
	size_t		j;
	bool		replace_mode;
	t_string	aux;
	size_t		init;

	i = 0;
	init = 0;
	replace_mode = true;
	replaced  = ft_strdup ("");
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			replace_mode  = !replace_mode;
		if (replace_mode && str[i] == '$')
		{
			before = ft_substr(str, init, i - init);
			replaced = ft_strjoin(replaced, before);
			j = expansor_find_end_var(str, i);
			aux = ft_substr(str, i, j);
			if (aux == NULL)
				error_system_crash("Error at memory malloc\n");
			replaced = expansor_replace_var_content(&replaced, aux, env);
			i = i + j;
			init = i;
		}
		i++;
	}
	return (replaced);
}

size_t	expansor_find_end_var(t_string str, size_t init)
{
	size_t	j;

	j = 1;
	if (ft_isdigit(str[init + j]) == 1)
		return (j);
	while (str[init + j] != '\0')
	{
		if (ft_isalnum(str[init + j]) == 0)
			break;
		j++;
	}
	return (j);
}

t_string	expansor_replace_var(t_string str, size_t i, size_t j, t_var var)
{
	t_string	replaced;
	t_string	before;
	t_string	after;
	size_t		len;
	t_var		*var;

	len = ft_stren(str);
	before = ft_substring(str, 0, i);
	if (before == NULL)
		error_system_crash("Error at memory malloc\n");
	after = ft_substring(str, i + j, len);
	if (after == NULL)
		error_system_crash("Error at memory malloc\n");
	
}
*/