/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:16:01 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/29 00:44:33 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
