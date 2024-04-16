/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:59:43 by gabriel           #+#    #+#             */
/*   Updated: 2024/04/16 08:20:57 by greus-ro         ###   ########.fr       */
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
	//t_path			path;
	t_env_var		*path;
	struct termios	termios;
	
}	t_minishell_cfg;

typedef struct s_minishell_status
{
	t_bool			run;
	int				return_status;
}	t_minishell_status;

typedef struct s_minishell
{
	t_minishell_status	status;
	t_minishell_cfg		cfg;
}	t_minishell;

t_minishell	ft_minishell_new(char **env);
void		ft_minishell_destroy(t_minishell shell);
t_bool		ft_minishell_cfg_load(t_minishell_cfg *cfg, char **env);
t_bool		ft_minishell_cfg_unload(t_minishell_cfg *cfg);
void		ft_minishell_cfg_debug(t_minishell_cfg *cfg);
void		ft_minishell_stat_init(t_minishell_status *stat);
void		ft_minishell_stat_destroy(t_minishell_status *stat);
t_bool		ft_minishell_check(t_minishell shell);

#endif