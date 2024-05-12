/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:56:27 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/12 23:29:30 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

int	builtin_pwd(t_minishell *shell, t_cmd cmd)
{
	(void)cmd;
	ft_putendl_fd(shell->cfg.pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
