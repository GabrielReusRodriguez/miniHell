/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:34:19 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/14 23:52:54 by gabriel          ###   ########.fr       */
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

// /char	*get_next_line(int fd);
/*
static	void	cmd_heredoc_find_endvar(t_string heredoc, size_t *i, size_t *end)
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
static t_string	cmd_heredoc_expand_vars(t_string  heredoc, t_environment env)
{
	t_string	value;
	size_t		i;
	size_t		offset;
//	t_string	aux;
	
	value = ft_strdup("");
	ptr_check_malloc_return(value, "Error at memory malloc.\n");
	i = 0;
	while (heredoc[i] != '\0')
	{
		if (heredoc[i] == '$')
		{
			offset = expansor_vars_find_end_var(heredoc, i);
			offset++;
		}
		i++;
	}

	(void)env;
	(void)heredoc;

	value = ft_strdup("");
	ptr_check_malloc_return(value, "Error at memory malloc\n.");
	return (value);
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
		here_doc = ft_strjoin(here_doc, " ");
		free (aux);
		ptr_check_malloc_return(here_doc, "Error at memory malloc\n.");
		aux = here_doc;
		here_doc = ft_strjoin(here_doc, next_line);
		ptr_check_malloc_return(here_doc, "Error at memory malloc\n.");
		free (aux);
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
