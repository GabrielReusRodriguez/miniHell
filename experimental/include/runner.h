/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:00:55 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/26 20:34:33 by gabriel          ###   ########.fr       */
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

int     runner_run_cmd_set(t_minishell *shell, t_cmd_set *cmd_set);
void	runner_get_status(t_minishell *shell,t_cmd_set *cmd_set);

#endif