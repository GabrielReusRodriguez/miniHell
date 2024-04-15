/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:59:43 by gabriel           #+#    #+#             */
/*   Updated: 2024/04/15 20:05:18 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218
https://achrafbelarif.medium.com/42cursus-minishell-29cd25f972e6

stty -a nos muestra las propiedades de la bash.
*/
#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include <termios.h>
# include "ft_environment.h"
# include "ft_datatypes.h"

#define MINISHELL_PROMPT "minishell> "

typedef struct 	s_minishell_cfg
{
	t_environment	env;
	struct termios	termios;
	
}	t_minishell_cfg;

t_bool	ft_minishell_cfg_load(t_minishell_cfg *cfg, char **env);
t_bool	ft_minishell_cfg_unload(t_minishell_cfg *cfg);
void	ft_minishell_cfg_debug(t_minishell_cfg *cfg);

#endif