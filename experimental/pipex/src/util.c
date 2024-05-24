/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 23:15:51 by abluis-m          #+#    #+#             */
/*   Updated: 2024/04/25 00:57:59 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		perror("malloc");
		exit(errno);
	}
	return (ptr);
}

void	close_pipes(t_pipex pipex, int *std_tmp)
{
	dup_tmp(std_tmp, OUT);
	if (pipex.fd[0].fd != -1)
		close(pipex.fd[0].fd);
	if (pipex.fd[1].fd != -1)
		close(pipex.fd[1].fd);
	if (pipex.heredoc)
		unlink("/tmp/herepipex");
}

void	dup_tmp(int *std_tmp, int flag)
{
	if (flag == IN)
	{
		std_tmp[0] = dup(STDIN_FILENO);
		std_tmp[1] = dup(STDOUT_FILENO);
		if (std_tmp[0] < 0 || std_tmp[1] < 0)
			ft_error(errno, NULL);
	}
	if (flag == OUT)
	{
		if (dup2(std_tmp[0], STDIN_FILENO) < 0)
			ft_error(errno, NULL);
		if (dup2(std_tmp[1], STDOUT_FILENO) < 0)
			ft_error(errno, NULL);
		if (close(std_tmp[0]) < 0)
			ft_error(errno, NULL);
		if (close(std_tmp[1]) < 0)
			ft_error(errno, NULL);
	}
}

void	*free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}
