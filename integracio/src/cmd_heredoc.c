/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:34:19 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/23 18:26:59 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "cmd.h"
#include "environment.h"
#include "redirect.h"
#include "libft.h"
#include "ptr.h"
#include "get_next_line.h"
#include "error_handler.h"
#include "expansor.h"
#include "txt_utils.h"
#include "get_next_line.h"

static	void	cmd_heredoc_treat_var(t_expansor *expansor, t_string *acum, \
					t_minishell shell)
{
	t_string	aux;
	t_string	var_value;
	t_var		*var;	
	size_t		offset;

	offset = expansor_vars_find_end_var(expansor->str, expansor->i + 1);
	aux = ft_substr(expansor->str, expansor->i + 1, offset);
	ptr_check_malloc_return(aux, "Error at memory malloc.\n");
	var = env_get_var(shell.cfg.env, aux);
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

static t_string	cmd_heredoc_expand_vars(t_string heredoc, t_minishell shell)
{
	t_string	acum;
	t_expansor	expansor;

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
			cmd_heredoc_treat_var(&expansor, &acum, shell);
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
		ft_putstr_fd(">", STDOUT_FILENO);
		next_line = get_next_line(STDIN_FILENO);
		if (next_line == NULL || ft_strcmp(limit, next_line) == 0)
		{
			free (next_line);
			break ;
		}
		here_doc = text_join(here_doc, next_line);
		aux = here_doc;
		here_doc = ft_strjoin(here_doc, "\n");
		ptr_check_malloc_return(here_doc, "Error at memory malloc\n.");
		free (aux);
	}
	return (here_doc);
}

void	cmd_heredoc(t_cmd *cmd, t_minishell shell)
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
			if (redir->target->type != TOKEN_TYPE_WORD_DQUOTE && \
					redir->target->type != TOKEN_TYPE_WORD_SQUOTE)
			{
				aux = cmd->here_doc;
				cmd->here_doc = cmd_heredoc_expand_vars(cmd->here_doc, shell);
				free (aux);
			}
		}
		node = node->next;
	}
}
