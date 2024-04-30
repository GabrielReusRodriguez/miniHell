/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:19:00 by abluis-m          #+#    #+#             */
/*   Updated: 2024/04/20 15:22:41 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

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
