/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:19:00 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/25 18:23:20 by greus-ro         ###   ########.fr       */
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
		prompt = ft_strdup(MINISHELL_PROMPT);
	else
	{
		prompt = ft_strjoin("minishell:\033[1;34m", cwd);
		ptr_check_malloc_return(prompt, "Error at memory malloc.\n");
		aux = prompt;
		prompt = ft_strjoin(prompt, "\033[0m$ ");
		ptr_check_malloc_return(prompt, "Error at memory malloc.\n");
		free (aux);
		free(cwd);
	}
	return (prompt);
}
