/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:00:55 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/29 01:02:46 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNNER_H
# define RUNNER_H

# include "cmd.h"
# include "minishell.h"

# define PIPE_READ_FD 0
# define PIPE_WRITE_FD 1

typedef struct s_run_env
{
	size_t		num_cmd;
	size_t		total_cmd;
	t_string	*paths;
	t_string	*envp;
}   t_run_env;

/*
	runner.c
*/
int     runner_run_cmd_set(t_minishell *shell, t_cmd_set *cmd_set);
int     runner_run_cmd(t_minishell *shell, t_cmd_set *cmd_set, t_run_env run_env);
void	runner_get_status(t_minishell *shell,t_cmd_set *cmd_set);
int     runner_run_cmd_set(t_minishell *shell, t_cmd_set *cmd_set);

/*
	runner_utils.c
*/
bool	runner_islastcmd(t_run_env run_env);
bool	runner_is_unique_builtin_cmd(t_cmd_set *cmd_set);
bool	runner_get_exec(t_cmd *cmd, t_string *paths);

/*
	runner_redirect.c
*/
bool	runner_treat_inputredir(t_cmd *cmd);
void	runner_treat_outputredir(t_cmd *cmd, t_run_env run_env);

/*
	runner_parent.c
*/
int	runner_parent_process(t_cmd *cmd, t_run_env run_env);

/*
	runner_child.c
*/
void	runner_child_process(t_minishell *shell, t_cmd *cmd, t_run_env run_env);

#endif