/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:00:30 by abluis-m          #+#    #+#             */
/*   Updated: 2024/06/02 21:12:03 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"
#include "builtin.h"
#include "runner.h"

int	cmd_run(t_minishell *shell, t_cmd cmd)
{
	int		code;

	code = 0;
	if (cmd_isbuiltin(cmd))
		code = builtin_run(shell, cmd);
	return (code);
}

int	cmd_set_run(t_minishell *shell, t_cmd_set cmd_set)
{
	int	code;

	code = runner_run_cmd_set(shell, &cmd_set);
	return (code);
}
