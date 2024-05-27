/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:45:59 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/27 22:48:51 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "cmd.h"
#include "tokens.h"
#include "libft.h"
#include "parser.h"
#include "debug.h"
#include "redirect.h"
#include "error_handler.h"
#include "ptr.h"

//TODO: WORK IN PROGRESS.....
t_cmd	cmd_new(void)
{
	t_cmd	cmd;

	cmd.exec = NULL;
	cmd.args = NULL;
	cmd.redir_in = NULL;
	cmd.redir_out = NULL;
	cmd.status = -1;
	cmd.here_doc = NULL;
    cmd.fd_input = -1;
    cmd.fd_output = -1;
	return (cmd);
}

void	cmd_destroy(t_cmd *cmd)
{
	if (cmd->exec != NULL)
		token_free(cmd->exec);
	if (cmd->args != NULL)
		ft_lstclear(&cmd->args, token_free_node);
	if (cmd->redir_in != NULL)
		ft_lstclear(&cmd->redir_in, redirect_freenode);
	if (cmd->redir_out != NULL)
		ft_lstclear(&cmd->redir_out, redirect_freenode);
	if (cmd->here_doc != NULL)
		free(cmd->here_doc);
}

void	cmd_destroy_set(t_cmd_set *cmd_set)
{
	size_t	i;

	if (cmd_set->cmds != NULL)
	{
		i = 0;
		while (i < cmd_set->cmd_count)
		{
			cmd_destroy(cmd_set->cmds + i);
			i++;
		}
		free(cmd_set->cmds);
	}
}

t_cmd_set	cmd_create_set(t_token_set token_set)
{
	t_cmd_set	cmd_set;
	size_t		i;

	cmd_set.cmd_count = parser_count_cmds(token_set);
	if (cmd_set.cmd_count == 0)
	{
		cmd_set.cmds = NULL;
		return (cmd_set);
	}
	cmd_set.cmds = (t_cmd *)safe_malloc(cmd_set.cmd_count * sizeof(t_cmd));
	i = 0;
	while (i < cmd_set.cmd_count)
	{
		cmd_set.cmds[i] = cmd_new();
		i++;
	}
	return (cmd_set);
}

t_string    *cmd_join_exec_and_args(t_cmd cmd)
{
	t_string	*argv;
	size_t		size;
	size_t		j;
	t_list		*node;

	j = 0;
	size = ft_lstsize(cmd.args);
	//argv = safe_malloc((size + 1) * sizeof(t_string));
	argv = (t_string *)malloc((size + 2) * sizeof(t_string));
	argv[j] = ft_strdup(cmd.exec->value);
    ptr_check_malloc_return(argv[j], "Error at memory malloc.\n");
    j++;
	node = cmd.args;
	while (node != NULL)
	{
		argv[j] = ft_strdup(((t_token *)node->content)->value);
        ptr_check_malloc_return(argv[j], "Error at memory malloc.\n");
		node = node->next;
		j++;
	}
	argv[j] = NULL;
	return (argv);
}