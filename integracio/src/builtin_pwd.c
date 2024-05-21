/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:56:27 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/21 20:55:34 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"
#include "libft.h"
#include "path.h"

int	builtin_pwd(t_minishell *shell, t_cmd cmd)
{
	/*
	(void)cmd;
	ft_putendl_fd(shell->cfg.pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);	
	*/
	t_string path;

	(void)shell;
	(void)cmd;
	path =  path_getcwd();
	if (path == NULL)
		return (EXIT_FAILURE);
	ft_putendl_fd(path, STDOUT_FILENO);
	free (path);
	return (EXIT_SUCCESS);
}
