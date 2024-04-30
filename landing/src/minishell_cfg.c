/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cfg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:19:55 by abluis-m          #+#    #+#             */
/*   Updated: 2024/04/20 15:23:30 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"
#include "libft.h"

bool	minishell_cfg_load(t_minishell_cfg *cfg, char **env)
{
	t_env_var	*var;
	t_list		*node;

	cfg->env.env = env;
	cfg->env.vars = env_init(env);
	if (cfg->env.vars == NULL)
		return (false);
	node = cfg->env.vars;
	while (node != NULL)
	{
		var = (t_env_var *)node->content;
		if (ft_strcmp("PATH", var->var) == 0)
		{
			cfg->path = var;
			break ;
		}
		node = node->next;
	}
	return (true);
}

bool	minishell_cfg_unload(t_minishell_cfg *cfg)
{
	env_destroy(&cfg->env);
	return (true);
}
