/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:00:55 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/25 01:18:55 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNNER_H
# define RUNNER_H

# include "cmd.h"
# include "minishell.h"

int     runner_run_cmd_set(t_minishell *shell, t_cmd_set *cmd_set);
void	runner_get_status(t_minishell *shell,t_cmd_set *cmd_set);

#endif