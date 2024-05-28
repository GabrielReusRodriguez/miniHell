/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:05:22 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/27 19:16:43 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

int	handle_redir_in(t_minishell *shell, t_cmd_set *cmd_set, int pos)
{
	(void)shell;
	(void)cmd_set;
	(void)pos;
	exit (EXIT_SUCCESS);
}

int	clean_fd(t_minishell *shell, t_cmd_set *cmd_set, int pos)
{
	(void)shell;
	(void)cmd_set;
	(void)pos;
	exit (EXIT_SUCCESS);
}
