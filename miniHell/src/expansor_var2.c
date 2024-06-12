/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_var2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:04:11 by gabriel           #+#    #+#             */
/*   Updated: 2024/06/12 18:01:13 by gabriel          ###   ########.fr       */
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
#include "parser.h"

/*
	We replace the value of the var $?
*/
static t_string	expansor_vars_replace_status(t_string acum, \
					t_expansor *limits, t_minishell shell)
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

/*
	We treat the case of $$ => we print a $
*/
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

t_string	expansor_vars_add_home(t_string acum, t_expansor *limits, \
				t_environment *env)
{
	t_var		*var;
	t_string	str_var;
	t_string	res;

	var = env_get_var(*env, "HOME");
	if (var == NULL)
	{
		res = ft_strdup("~");
		ptr_check_malloc_return(res, "Error at memory malloc.\n");
		free(acum);
		limits->i++;
		limits->init = limits->i;
		return (res);
	}
	str_var = ft_strdup(var->value);
	ptr_check_malloc_return(str_var, "Error at memory malloc.\n");
	res = text_join(acum, str_var);
	limits->i++;
	limits->init = limits->i;
	return (res);
}

t_string	expansor_vars_treat_dollar(t_expansor *limits, \
					t_string expanded, t_minishell shell, t_token *next_t)
{
	t_string	substring;

	if (limits->init < limits->i)
		expanded = expansor_vars_join_acumulated(expanded, *limits);
	if (limits->str[limits->i + 1] == '\0' && (next_t == NULL || \
				next_t->type == TOKEN_TYPE_SPACE))
		return (expansor_vars_add_dollar(expanded, limits));
	if (limits->str[limits->i + 1] == '?')
		return (expansor_vars_replace_status(expanded, limits, shell));
	substring = expansor_vars_get_var(limits->str, limits->i + 1, \
					&limits->init, shell);
	expanded = text_join(expanded, substring);
	limits->i = limits->init;
	return (expanded);
}

t_string	expansor_vars_treat_tilde(t_expansor *limits, \
						t_string expanded, t_minishell shell)
{
	t_string	substring;
	t_string	res;

	if (limits->init < limits->i)
		expanded = expansor_vars_join_acumulated(expanded, *limits);
	if (limits->i == 0 && \
			!limits->is_quoted && \
			(limits->str[limits->i + 1] == '\0' || \
			tokenizer_charinset(limits->str[limits->i + 1], \
					TOKENS_SEPARATORS PARSER_CMD_SEPARATORS) || \
					limits->str[limits->i + 1] == '/'))
		return (expansor_vars_add_home(expanded, limits, \
					&shell.cfg.env));
	else
	{
		substring = ft_strdup("~");
		ptr_check_malloc_return(substring, "Error at memory malloc.\n");
		res = text_join(expanded, substring);
		limits->i++;
		limits->init = limits->i;
		return (res);
	}
	return (expanded);
}
