/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:15:29 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/12 23:23:40 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "error_handler.h"
#include "perm.h"
#include "datatypes.h"
#include "libft.h"

void	*error_print(t_cstring msg)
{
	size_t	len;

	len = ft_strlen(msg);
	write(STDERR_FILENO, msg, len);
	return (NULL);
}

void	error_system_crash(t_cstring msg)
{
	error_print(msg);
	exit(EXIT_FAILURE);
}

void	put_cmd_error(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": Command not found\n", STDERR_FILENO);
}

void	put_file_error(int error_code, char *str)
{
	if (error_code == NO_READ || error_code == NO_WRITE
		|| error_code == NO_EXEC)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
	else if (error_code == NO_FILE)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
}

int	ft_error(int error_code, char *str)
{
	if (error_code == NO_COMMAND)
		put_cmd_error(str);
	else if (error_code >= 400 || error_code == NO_EXEC)
	{
		put_file_error(error_code, str);
		if (error_code != 126)
			error_code = 1;
	}
	else if (str)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		//ft_putstr_fd(": ", STDERR_FILENO);
		//ft_putendl_fd(strerror(error_code), STDERR_FILENO);
	}
	else
		perror("minishell");
	exit(error_code);
}