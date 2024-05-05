/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:56:27 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/05 17:41:31 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

int	builtin_pwd(t_minishell *shell, t_cmd cmd)
{
	(void)cmd;
	ft_putendl_fd(shell->cfg.pwd->value, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
