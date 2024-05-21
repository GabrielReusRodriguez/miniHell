/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cfg2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:19:55 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/22 00:02:09 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"
#include "libft.h"
#include "error_handler.h"
#include "ptr.h"

#include "path.h"
#include <stdio.h>

static  void    minishell_cfg_default_shlevel(t_minishell_cfg *cfg)
{	
	int			level;
	t_var		*env_var;
	t_var		var;
	t_string	str_level;

	env_var = env_get_var(cfg->env, "SHLVL");
	if (env_var == NULL)
	{
		var = var_new_wargs("SHLVL","1");
		if (env_add_var(&cfg->env, var) == NULL)
			error_system_crash("Error creating PWD var\n");
		var_destroy(&var);
	}
	else
	{
		level = ft_atoi(env_var->value);
		str_level = ft_itoa(level + 1);
		ptr_check_malloc_return(str_level, "Error at memory  malloc.\n");
		var = var_new_wargs("SHLVL", str_level);
		if (env_addorupdate_var(&cfg->env, var) == NULL)
			error_system_crash("Error creating PWD var\n");
		free (str_level);
		var_destroy(&var);
	}
}

static void		minishell_cfg_default_shell(t_minishell_cfg *cfg)
{
	t_var	var;

	var = var_new_wargs("SHELL", MINISHELL_NAME);
	if (env_addorupdate_var(&cfg->env, var) == NULL)
		error_system_crash("Error at memory malloc.\n");
	var_destroy(&var);

}

static	void	minishell_cfg_default_pwd(t_minishell_cfg *cfg)
{
	t_var		var;
	t_string	str_value;

	str_value = path_getcwd();
	if (str_value == NULL)
		return ;
	var = var_new_wargs("PWD", str_value);
	if (env_add_var(&cfg->env, var) == NULL)
		error_system_crash("Error creating PWD var\n");
	var_destroy(&var);
	free (str_value);
}

static void		minishell_cfg_default_oldpwd(t_minishell_cfg *cfg)
{
	t_var		var;
	t_string	str_value;

	str_value = path_getcwd();
	if (str_value == NULL)
		return ;
	var = var_new_wargs("OLDPWD", str_value);
	if (env_add_var(&cfg->env, var) == NULL)
		error_system_crash("Error creating OLDPWD var\n");
	var_destroy(&var);
	free (str_value);

}

void minishell_cfg_load_default(t_minishell_cfg *cfg)
{
	if (cfg->var_pwd == NULL)
		minishell_cfg_default_pwd(cfg);
	if (cfg->var_oldpwd == NULL)
		minishell_cfg_default_oldpwd(cfg);
	minishell_cfg_default_shlevel(cfg);
	minishell_cfg_default_shell(cfg);
}
