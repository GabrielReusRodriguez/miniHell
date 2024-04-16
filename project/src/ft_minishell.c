/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:44:14 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/16 20:24:09 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_minishell.h"

t_minishell	ft_minishell_new(char **env)
{
	t_minishell	shell;
	
	ft_minishell_cfg_load(&shell.cfg, env);
	ft_minishell_stat_init(&shell.status);
	return (shell);
}

void		ft_minishell_destroy(t_minishell shell)
{
	ft_minishell_cfg_unload(&shell.cfg);
}

t_bool		ft_minishell_check(t_minishell shell)
{
	if (shell.cfg.env.vars == NULL)
		return (FALSE);
	return (TRUE);
}
