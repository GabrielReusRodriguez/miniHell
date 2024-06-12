/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_var3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:04:11 by gabriel           #+#    #+#             */
/*   Updated: 2024/06/12 18:02:42 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"
#include "ptr.h"
#include "expansor.h"
#include "txt_utils.h"

/*
	We join the string cumulated when we replace vars with the new string
	we get expanding vars.
*/
t_string	expansor_vars_join_acumulated(t_string acum, t_expansor limits)
{
	t_string	res;
	t_string	substring;

	substring = ft_substr(limits.str, limits.init, limits.i - limits.init);
	ptr_check_malloc_return(substring, "Error at memory malloc\n.");
	res = text_join(acum, substring);
	return (res);
}

/*
	We have an structure to grt the chunks. 
		it is the init position of the chunk
		the i position that is the end of the chuink
		and str, the string.
	In this function we init the structure
*/
t_string	expansor_vars_replace_vars_init(t_expansor	*limits, \
					t_token token)
{
	t_string	expanded;

	expanded = ft_strdup("");
	ptr_check_malloc_return(expanded, "Error at memory malloc.\n");
	limits->i = 0;
	limits->init = 0;
	limits->is_quoted = token.type == TOKEN_TYPE_WORD_DQUOTE || \
			token.type == TOKEN_TYPE_WORD_SQUOTE;
	limits->str = token.value;
	return (expanded);
}

/*
The case if (limits->str[limits->i + 1] == '\0' && (next_t == NULL || 
next_t->type == TOKEN_TYPE_SPACE))

is to print the lonely $ because we now the next token is a space.
*/
static t_string	expansor_vars_replace_loop(t_string expanded, \
			t_expansor *limits, t_token *next_t, t_minishell shell)
{
	if (limits->str[limits->i] == '$')
		return (expansor_vars_treat_dollar(limits, expanded, shell, \
					next_t));
	else
	{
		if (limits->str[limits->i] == '~')
			return (expansor_vars_treat_tilde(limits, expanded, shell));
		else
			limits->i++;
	}
	return (expanded);
}

/*
	This is the function where we replace the vars found in token
	We get the token and the next token because we can find a $PA"TH" 
		it is a token $ and the next_t is a double quoted token. So
		we have to analize both.
*/
void	expansor_vars_replace_vars(t_token *token, t_token *next_t, \
			t_minishell shell)

{
	t_string			expanded;
	t_expansor			expansor;

	if (token->type == TOKEN_TYPE_WORD_SQUOTE)
		return ;
	expanded = expansor_vars_replace_vars_init(&expansor, *token);
	while (token->value[expansor.i] != '\0')
	{
		expanded = expansor_vars_replace_loop(expanded, &expansor, next_t, \
						shell);
	}
	if (expansor.init < expansor.i)
		expanded = expansor_vars_join_acumulated(expanded, expansor);
	free (token->value);
	token->value = expanded;
}
