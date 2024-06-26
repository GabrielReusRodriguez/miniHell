/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:49:13 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/23 18:58:35 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "tokens.h"
#include "error_handler.h"
#include "ptr.h"
#include <stdio.h>

/*
	We removes the single quote from text.
*/
static t_string	expansor_treat_squoted(size_t *i, t_string str)
{
	t_string	chunk;
	size_t		j;

	j = 0;
	while (str[*i + 1 + j] != '\0' && str[*i + 1 + j] != '\'')
		j++;
	if (str[*i + j + 1] == '\0')
	{
		chunk = ft_substr(str, *i, j + 1);
		ptr_check_malloc_return(chunk, "Error at memory malloc\n.");
		*i = *i + j + 1;
	}
	else
	{
		chunk = ft_substr(str, *i, j + 1);
		ptr_check_malloc_return(chunk, "Error at memory malloc\n.");
		*i = *i + j + 1;
	}
	return (chunk);
}

/*
	Removes the quotes of text sorrounded by double quotes.
*/
static t_string	expansor_treat_dquoted(size_t *i, t_string str)
{
	t_string	chunk;
	size_t		j;

	j = 0;
	*i = *i + 1;
	while (str[*i + j] != '\0' && str[*i + j] != '\"')
		j++;
	if (str[*i + j] == '\0')
	{
		chunk = ft_substr(str, *i, j);
		ptr_check_malloc_return(chunk, "Error at memory malloc\n.");
		*i = *i + j;
	}
	else
	{
		chunk = ft_substr(str, *i, j);
		ptr_check_malloc_return(chunk, "Error at memory malloc\n.");
		*i = *i + j + 1;
	}
	return (chunk);
}

/*
	Here we treat  the normal text  ( we omit double quotes and 
		simple quotes)
*/
static t_string	expansor_treat_normal(size_t *i, t_string str)
{
	t_string	chunk;
	size_t		j;

	j = 0;
	while (str[*i + j] != '\0' && str[*i + j] != '\"' && str[*i + j] != '\'')
		j++;
	if (str[*i + j] == '\0')
	{
		chunk = ft_substr(str, *i, j);
		ptr_check_malloc_return(chunk, "Error at memory malloc\n.");
		*i = *i + j;
	}
	else
	{
		chunk = ft_substr(str, *i, j - 1);
		ptr_check_malloc_return(chunk, "Error at memory malloc\n.");
		*i = *i + j;
	}
	return (chunk);
}

/*
	Here we treat the different cases, normal text and double quote text
*/
static t_string	expansor_treat_expand(size_t *i, t_string str)
{
	if (str[*i] == '\"')
		return (expansor_treat_dquoted(i, str));
	else
		return (expansor_treat_normal(i, str));
}

/*
	Here we remove the quotes from text of a token,
	We look for a ' char because we can find a token :
		asdasdwe'text in simplequote'asdasda.
*/
void	expansor_expand(t_token *token)
{
	size_t		i;
	t_string	aux;
	t_string	acum;
	t_string	chunk;

	i = 0;
	acum = ft_strdup("");
	ptr_check_malloc_return(acum, "Error at memory malloc\n.");
	while (token->value[i] != '\0')
	{
		if (token->value[i] == '\'')
			chunk = expansor_treat_squoted(&i, token->value);
		else
			chunk = expansor_treat_expand(&i, token->value);
		aux = acum;
		acum = ft_strjoin(aux, chunk);
		ptr_check_malloc_return(acum, "Error at memory malloc\n.");
		free(aux);
		free (chunk);
	}
	free(token->value);
	token->value = acum;
}
