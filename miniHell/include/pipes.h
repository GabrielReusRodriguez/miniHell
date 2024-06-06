/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:47:45 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/31 00:59:45 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

/*
	pipes.c
*/
void	pipes_init(int *pipe);
void	pipes_close_pipe(int pipe[2]);
void	pipes_new(int pipes[2]);
void	pipes_dup2(int oldfd, int newfd);
int		pipes_dup(int oldfd);

#endif