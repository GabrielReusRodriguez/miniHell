/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:16:01 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/31 21:16:39 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "fd.h"

void	pipes_init(int *pipe)
{
	pipe[0] = -1;
	pipe[1] = -1;
}

void	pipes_close_pipe(int pipe[2])
{
	fd_close(pipe[0]);
	fd_close(pipe[1]);
}

void	pipes_new(int pipes[2])
{
	if (pipe(pipes) < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

void	pipes_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) < 0)
	{
		perror ("Error");
		exit(EXIT_FAILURE);
	}
}

int	pipes_dup(int oldfd)
{
	int	result;

	result = dup(oldfd);
	if (result < 0)
	{
		perror ("Error");
		exit(EXIT_FAILURE);
	}
	return (result);
}
