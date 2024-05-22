/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_var2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:04:11 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/22 22:51:59 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"
#include "environment.h"
#include "error_handler.h"
#include "tokens.h"
#include "ptr.h"
#include "expansor.h"
#include "txt_utils.h"
#include "minishell.h"

//#include <stdio.h>

static t_string	expansor_vars_replace_status(t_string acum, t_expansor *limits, t_minishell shell)
{
	t_string	substring;
	t_string	res;

    substring = ft_itoa(shell.status.return_status);
    ptr_check_malloc_return(substring, "Error at memory malloc.\n");
	res = text_join(acum, substring);
	limits->i = limits->i + 2;
	limits->init = limits->i;
	return (res);
}

static t_string	expansor_vars_add_dollar(t_string acum, t_expansor *limits)
{
	t_string	substring;
	t_string	res;

	substring = ft_strdup("$");
    ptr_check_malloc_return(substring, "Error at memory malloc.\n");
	res = text_join(acum, substring);
	limits->i++;
	limits->init = limits->i;
	return (res);
}

static t_string	expansor_vars_replace_vars_init(t_expansor	*limits, \
					t_string str)
{
	t_string	expanded;

	expanded = ft_strdup("");
    ptr_check_malloc_return(expanded, "Error memory malloc.\n");
	limits->i = 0;
	limits->init = 0;
	limits->str = str;
	return (expanded);
}

/*
El caso  if (limits->str[limits->i + 1] == '\0' && (next_t == NULL || 
next_t->type == TOKEN_TYPE_SPACE))
es para que no pinte el dolar antes en $"PATH" ya que como un chunk seria $ 
y el siguiente
seria DQWORD, pintaria el dolar y luego la var.
*/
static t_string	expansor_vars_replace_loop(t_string expanded, \
			t_expansor *limits, t_token *next_t, t_minishell shell)
{
	t_string	substring;

	if (limits->str[limits->i] == '$')
	{
		if (limits->init < limits->i)
			expanded = expansor_vars_join_acumulated(expanded, *limits);
		if (limits->str[limits->i + 1] == '\0' && (next_t == NULL || \
					next_t->type == TOKEN_TYPE_SPACE))
		{
			expanded = expansor_vars_add_dollar(expanded, limits);
			return (expanded);
		}
		if (limits->str[limits->i + 1] == '?')
		{
			expanded = expansor_vars_replace_status(expanded, limits, shell);
			return (expanded);
		}
		substring = expansor_vars_get_var(limits->str, limits->i + 1, \
						&limits->init, shell);
		expanded = text_join(expanded, substring);
		limits->i = limits->init;
	}
	else
		limits->i++;
	return (expanded);
}

void	expansor_vars_replace_vars(t_token *token, t_token *next_t, \
			t_minishell shell)

{
	t_string			expanded;
	t_expansor			expansor;

	if (token->type == TOKEN_TYPE_WORD_SQUOTE)
		return ;
	expanded = expansor_vars_replace_vars_init(&expansor, token->value);
	while (token->value[expansor.i] != '\0')
	{
		expanded = expansor_vars_replace_loop(expanded, &expansor, next_t, shell);
	}
	if (expansor.init < expansor.i)
		expanded = expansor_vars_join_acumulated(expanded, expansor);
	free (token->value);
	token->value = expanded;
}
