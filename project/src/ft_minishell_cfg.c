/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_cfg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:53:48 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/16 08:53:53 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "ft_environment.h"
#include "libft.h"

t_bool	ft_minishell_cfg_load(t_minishell_cfg *cfg, char **env)
{
	t_env_var	*var;
	t_list		*node;

	cfg->env.env = env;
	cfg->env.vars = ft_env_init(env);
	if (cfg->env.vars == NULL)
		return (FALSE);
	node = cfg->env.vars;
	while (node != NULL)
	{
		var = (t_env_var *)node->content;
		if (ft_strcmp("PATH", var->var) == 0)
		{
			cfg->path = var;
			break;
		}
		node = node->next;
	}
	return (TRUE);
}

t_bool		ft_minishell_cfg_unload(t_minishell_cfg *cfg)
{
		ft_env_destroy(&cfg->env);
		return (TRUE);
}