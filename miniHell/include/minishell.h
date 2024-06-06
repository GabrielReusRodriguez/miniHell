/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:33:43 by abluis-m          #+#    #+#             */
/*   Updated: 2024/06/06 18:19:48 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "datatypes.h"
# include "environment.h"
# include "var.h"
# include <termios.h>

# define SIGNAL_MODE_INTERACTIVE 0
# define SIGNAL_MODE_DEFAULT 2
# define SIGNAL_MODE_NOOP 3

# define MINISHELL_PROMPT	"msh:$ "
# define MINISHELL_NAME     "minishell"

typedef struct s_minishell_cfg
{
	t_environment	env;
	t_var			*var_path;
	t_var			*var_pwd;
	t_var			*var_oldpwd;
	int				old_stdin;
	int				old_stdout;
}	t_minishell_cfg;

typedef struct s_minishell_status
{
	bool			run;
	int				return_status;
}	t_minishell_status;

typedef struct s_minishell
{
	t_minishell_status	status;
	t_minishell_cfg		cfg;
}	t_minishell;

/*
	minishell.c
*/
t_minishell	minishell_new(char **env);
void		minishell_destroy(t_minishell shell);
//void		minishell_cfg_debug(t_minishell_cfg *cfg);
bool		minishell_check(t_minishell shell);
t_string	minishell_get_prompt(void);

void		signal_set_mode(int mode);

/*
	minishell_stat.c
*/
void		minishell_stat_init(t_minishell_status *stat);
void		minishell_stat_destroy(t_minishell_status *stat);
//void		minishell_refresh_pwd_vars(t_minishell *shell, t_string new_cwd);

/*
	minishell_cfg.c
*/
bool		minishell_cfg_load(t_minishell_cfg *cfg, char **env);
bool		minishell_cfg_unload(t_minishell_cfg *cfg);
void		minishell_cfg_refresh_pwd_vars(t_minishell *shell, \
				t_string new_cwd);

/*
	minishell_cfg2.c
*/
void		minishell_cfg_load_default(t_minishell_cfg *cfg);

/*
    minishell_cfg3.c
*/
t_string	*minishell_path_2_vector(t_minishell shell);

/*
	main2.c
*/
char		*build_cmd_line(char **vector);

#endif
