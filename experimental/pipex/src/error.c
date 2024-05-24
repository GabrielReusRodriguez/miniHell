/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:59:39 by abluis-m          #+#    #+#             */
/*   Updated: 2024/04/25 16:33:56 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(t_cmd cmd)
{
	if (cmd.arg[0] == NULL)
		exit (0);
	if (cmd.perm == NO_COMMAND)
		ft_error(NO_COMMAND, cmd.arg[0]);
	if (cmd.perm == NO_EXEC)
		ft_error(NO_EXEC, cmd.arg[0]);
}

void	put_arg_error(void)
{
	ft_putstr_fd ("Usage:\n\n"
		"./pipex input_file cmd1 ... cmdN output_file\n"
		"./pipex here_doc delimiter cmd1 ... cmdN append_file\n",
		STDERR_FILENO);
}

void	put_cmd_error(char *str)
{
	ft_putstr_fd("Pipex: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": Command not found\n", STDERR_FILENO);
}

void	put_file_error(int error_code, char *str)
{
	if (error_code == NO_READ || error_code == NO_WRITE
		|| error_code == NO_EXEC)
	{
		ft_putstr_fd("Pipex: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
	else if (error_code == NO_FILE)
	{
		ft_putstr_fd("Pipex: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
}

int	ft_error(int error_code, char *str)
{
	if (error_code == ARG_ERROR)
		put_arg_error();
	else if (error_code == NO_COMMAND)
		put_cmd_error(str);
	else if (error_code >= 400 || error_code == NO_EXEC)
	{
		put_file_error(error_code, str);
		if (error_code != 126)
			error_code = 1;
	}
	else if (str)
	{
		ft_putstr_fd("Pipex: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(error_code), STDERR_FILENO);
	}
	else
		perror("Pipex");
	exit(error_code);
}
