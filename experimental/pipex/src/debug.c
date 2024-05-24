/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:27:05 by abluis-m          #+#    #+#             */
/*   Updated: 2024/04/25 17:05:19 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	debug_arg(char **av, char **ev)
{
	debug_tab(ev, "ENVIRONMENT:");
	debug_tab(av, "ARGUMENTS:");
}

void	debug_tab(char **tab, char *msg)
{
	int	i;

	if (msg)
	{
		ft_putendl_fd("DEBUG_MODE = 1", 2);
		ft_putendl_fd(msg, 2);
	}
	i = 0;
	while (tab[i])
		ft_putendl_fd(tab[i++], 2);
}

void	debug_str(char *str, char *msg)
{
	if (msg)
	{
		ft_putendl_fd("DEBUG_MODE = 1", 2);
		ft_putendl_fd(msg, 2);
	}
	ft_putendl_fd(str, 2);
}

void	debug_cmd(t_cmd *command)
{
	ft_putstr_fd("\nDEBUG_MODE = 1", 2);
	ft_putstr_fd("\nID: ", 2);
	ft_putnbr_fd(command->id, 2);
	ft_putstr_fd("\nNAME: ", 2);
	ft_putstr_fd(command->name, 2);
	ft_putstr_fd("\nPERM: ", 2);
	ft_putnbr_fd(command->perm, 2);
	ft_putstr_fd("PATH: ", 2);
	ft_putendl_fd(command->path, 2);
	debug_tab(command->arg, NULL);
	ft_putstr_fd("\n", 2);
}
