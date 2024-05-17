/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:56:27 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/17 19:16:16 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"
#include "libft.h"

int	builtin_pwd(t_minishell shell, t_cmd cmd)
{
	(void)cmd;
	ft_putendl_fd(shell.cfg.pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);	
}
