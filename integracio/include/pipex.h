/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:17:11 by abluis-m          #+#    #+#             */
/*   Updated: 2024/04/30 17:30:08 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"

# define PERM_OK 0
# define NO_FILE 400
# define NO_READ 404
# define NO_WRITE 402
# define NO_EXEC 126
# define NO_COMMAND 127

typedef struct s_command
{
	int		id;
	char	*name;
	char	*path;
	char	**args;
	int		builtin;
	int		perm;
}	t_command;

typedef struct s_fd
{
	int		fd;
	char	*name;
	int		perm;
}	t_fd;

typedef struct s_pipex
{
	int		cmd_count;
	char	**env;
	t_fd	fd[2];
}	t_pipex;

#endif
