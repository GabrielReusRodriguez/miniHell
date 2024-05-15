/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:34:19 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/15 22:45:08 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "cmd.h"
#include "environment.h"
#include "redirect.h"
#include "libft.h"
#include "ptr.h"
#include "get_next_line.h"
#include "error_handler.h"
#include "expansor.h"
#include "txt_utils.h"

// /char	*get_next_line(int fd);
/*
static	void	cmd_heredoc_find_endvar(t_string heredoc, size_t i)
{
	size_t	offset;
	
	offset = 1;
	if (ft_isalpha(heredoc[*i + offset]) == 1)
	{
		offset++;
		while (ft_isalnum(heredoc[*i + offset]) == 1)
			offset++;
	}
}
*/

/*
typedef struct s_expansor
{
	size_t		i;
	size_t		init;
	t_string	str;
}	t_expansor;
*/

/*
t_string	text_join(t_string origin, t_string destiny)
{
	t_string	res;

	res = ft_strjoin(origin, destiny);
	free (origin);
	free (destiny);
	if (res == NULL)
		error_system_crash("Error at memory malloc\n");
	return (res);
}

*/
// t_string	expansor_vars_join_acumulated(t_string acum, t_expansor limits)

static	void	cmd_heredoc_treat_var(t_expansor *expansor, t_string *acum, t_environment env)
{
	t_string	aux;
	t_string	var_value;
	t_var		*var;	
	size_t		offset;

	offset = expansor_vars_find_end_var( expansor->str, expansor->i + 1);
	aux = ft_substr(expansor->str, expansor->i + 1, offset);
	ptr_check_malloc_return(aux, "Error at memory malloc.\n");
	var = env_get_var(env, aux);
	free (aux);
	if (var == NULL)
		var_value = ft_strdup("");
	else
		var_value = ft_strdup(var->value);
	ptr_check_malloc_return(var_value, "Error at memory malloc.\n");
	*acum = text_join(*acum, var_value);
	expansor->i = expansor->i + offset + 1;
	expansor->init = expansor->i;
}

static t_string	cmd_heredoc_expand_vars(t_string  heredoc, t_environment env)
{
	t_string	acum;
	t_expansor  expansor;

	expansor.i = 0;
	expansor.init = 0;
	expansor.str = heredoc;
	acum = ft_strdup("");
	ptr_check_malloc_return(acum, "Error at memory malloc.\n");
	while (heredoc[expansor.i] != '\0')
	{
		if (heredoc[expansor.i] == '$')
		{
			if (expansor.init < expansor.i)
				acum = expansor_vars_join_acumulated(acum, expansor);
			cmd_heredoc_treat_var(&expansor, &acum, env);
		}
		if (heredoc[expansor.i] != '\0')
			expansor.i++;
	}
	if (expansor.init < expansor.i)
		acum = expansor_vars_join_acumulated(acum, expansor);
	return (acum);
}

static	t_string	cmd_heredoc_get(t_string limit)
{
	t_string	here_doc;
	t_string	next_line;
	t_string	aux;

	here_doc = ft_strdup("");
	ptr_check_malloc_return(here_doc, "Error at memory malloc\n.");
	next_line = here_doc;
	while (next_line != NULL)
	{
		next_line = readline(">");
		if (next_line == NULL || ft_strcmp(limit, next_line) == 0)
			break;
		aux = here_doc;
		here_doc = ft_strjoin(here_doc, "\n");
		free (aux);
		ptr_check_malloc_return(here_doc, "Error at memory malloc\n.");
		here_doc = text_join(here_doc, next_line);
	}
	return (here_doc);
}

void    cmd_heredoc(t_cmd *cmd, t_environment env)
{
	t_redirect	*redir;
	t_list		*node;
	t_string	aux;

	if (cmd->redir_in == NULL)
		return ;
	node = cmd->redir_in;
	while (node != NULL)
	{
		redir = (t_redirect *)node->content;
		if (redir->type->type == TOKEN_TYPE_RED_HERE_DOC)
		{
			ptr_free(cmd->here_doc);
			cmd->here_doc = cmd_heredoc_get(redir->target->value);
			printf("redir target_type = %d\n", redir->target->type);
			if (redir->target->type != TOKEN_TYPE_WORD_DQUOTE && \
					redir->target->type != TOKEN_TYPE_WORD_SQUOTE)
			{
				aux = cmd->here_doc;
				cmd->here_doc = cmd_heredoc_expand_vars(cmd->here_doc, env);
				free (aux);
			}
		}
		node = node->next;
	}
}
