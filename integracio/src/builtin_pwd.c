/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:56:27 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/25 16:12:54 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"
#include "libft.h"
#include "path.h"

int	builtin_pwd(t_minishell *shell, t_cmd cmd)
{
	t_string	path;

	(void)shell;
	(void)cmd;
	path = path_getcwd();
	if (path == NULL)
		return (EXIT_FAILURE);
	ft_putendl_fd(path, STDOUT_FILENO);
	free (path);
	return (EXIT_SUCCESS);
}
