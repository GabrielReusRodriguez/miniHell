/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cfg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:19:55 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/05 19:36:50 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"
#include "libft.h"

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
			cfg->path = var;
		if (ft_strcmp("PWD", var->key) == 0)
			cfg->pwd = var;
		node = node->next;
	}
	//env_debug(cfg->env);
	return (true);
}

bool	minishell_cfg_unload(t_minishell_cfg *cfg)
{
	env_destroy(&cfg->env);
	return (true);
}
