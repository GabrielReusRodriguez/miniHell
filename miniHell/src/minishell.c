/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:19:00 by abluis-m          #+#    #+#             */
/*   Updated: 2024/06/04 20:57:01 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "path.h"
#include "ptr.h"

t_minishell	minishell_new(char **env)
{
	t_minishell	shell;

	minishell_cfg_load(&shell.cfg, env);
	minishell_stat_init(&shell.status);
	return (shell);
}

void	minishell_destroy(t_minishell shell)
{
	minishell_cfg_unload(&shell.cfg);
}

bool	minishell_check(t_minishell shell)
{
	if (shell.cfg.env.vars == NULL)
		return (false);
	return (true);
}

t_string	minishell_get_prompt(void)
{
	t_string	prompt;
	t_string	cwd;
	t_string	aux;

	cwd = path_getcwd();
	if (cwd == NULL)
	{
		prompt = ft_strdup(MINISHELL_PROMPT);
		ptr_check_malloc_return(prompt, "Error at memory malloc.\n");
	}
	else
	{
		prompt = ft_strjoin("msh:", cwd);
		ptr_check_malloc_return(prompt, "Error at memory malloc.\n");
		aux = prompt;
		prompt = ft_strjoin(prompt, "$ ");
		ptr_check_malloc_return(prompt, "Error at memory malloc.\n");
		free (aux);
		free(cwd);
	}
	return (prompt);
}
