/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cfg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:19:55 by abluis-m          #+#    #+#             */
/*   Updated: 2024/06/04 23:14:57 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"
#include "libft.h"
#include "error_handler.h"
#include "ptr.h"
#include "pipes.h"

#include "fd.h"
#include "path.h"
#include <stdio.h>

static void	minishell_cfg_init(t_minishell_cfg *cfg)
{
	cfg->var_path = NULL;
	cfg->var_pwd = NULL;
	cfg->var_oldpwd = NULL;
	cfg->old_stdin = pipes_dup(STDIN_FILENO);
	cfg->old_stdout = pipes_dup(STDOUT_FILENO);
}

bool	minishell_cfg_load(t_minishell_cfg *cfg, char **str_env)
{
	t_var		*var;
	t_list		*node;

	if (env_init(&cfg->env, str_env) == NULL)
		return (false);
	minishell_cfg_init(cfg);
	node = cfg->env.vars;
	while (node != NULL)
	{
		var = (t_var *)node->content;
		if (ft_strcmp("PATH", var->key) == 0)
			cfg->var_path = var;
		if (ft_strcmp("PWD", var->key) == 0)
			cfg->var_pwd = var;
		if (ft_strcmp("OLDPWD", var->key) == 0)
			cfg->var_oldpwd = var;
		node = node->next;
	}
	minishell_cfg_load_default(cfg);
	return (true);
}

bool	minishell_cfg_unload(t_minishell_cfg *cfg)
{
	env_destroy(&cfg->env);
	fd_close(cfg->old_stdin);
	fd_close(cfg->old_stdout);
	return (true);
}

void	minishell_cfg_refresh_pwd_vars(t_minishell *shell, t_string new_cwd)
{
	if (shell->cfg.var_oldpwd != NULL)
	{
		free (shell->cfg.var_oldpwd->value);
		if (shell->cfg.var_pwd != NULL)
			shell->cfg.var_oldpwd->value = ft_strdup(shell->cfg.var_pwd->value);
		else
			shell->cfg.var_oldpwd->value = ft_strdup(new_cwd);
		ptr_check_malloc_return(shell->cfg.var_oldpwd->value, \
			"Error at memory malloc\n.");
	}
	if (shell->cfg.var_pwd != NULL)
	{
		free (shell->cfg.var_pwd->value);
		shell->cfg.var_pwd->value = path_getcwd();
		ptr_check_malloc_return(shell->cfg.var_pwd->value, \
			"Error at memory malloc\n.");
	}
}
