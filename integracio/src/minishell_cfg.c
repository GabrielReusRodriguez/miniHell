/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cfg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:19:55 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/12 23:00:48 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"
#include "libft.h"
#include "error_handler.h"
#include "ptr.h"

bool	minishell_cfg_load(t_minishell_cfg *cfg, char **str_env)
{
	t_var		*var;
	t_list		*node;

	if (env_init(&cfg->env, str_env) == NULL)
		return (false);
	node = cfg->env.vars;
	while (node != NULL)
	{
		var = (t_var *)node->content;
		if (ft_strcmp("PATH", var->key) == 0)
			cfg->var_path = var;
		if (ft_strcmp("PWD", var->key) == 0)
			cfg->var_pwd = var;
		node = node->next;
	}
	if (cfg->var_pwd != NULL)
		cfg->pwd = ft_strdup(cfg->var_pwd->value);
	else
		cfg->pwd = ft_strdup("");
	if (cfg->pwd == NULL)
		error_system_crash("Error at memory malloc\n");
	return (true);
}

bool	minishell_cfg_unload(t_minishell_cfg *cfg)
{
	env_destroy(&cfg->env);
	ptr_free(cfg->pwd);
	return (true);
}
