/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:25:18 by abluis-m          #+#    #+#             */
/*   Updated: 2024/04/24 21:02:01 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

int	check_eof(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (TRUE);
	while (s1[i] || s2[2])
	{
		if (s1[i] != s2[i])
		{
			if (s2[i] == '\n')
				return (FALSE);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int	set_heredoc(char *eof)
{
	char	*line;
	int		tmp_fd;

	tmp_fd = open("/tmp/heredoc_pipex", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (tmp_fd < 0)
		return (ft_error(errno, "error opening heredoc"), 1);
	while (42)
	{
		write(1, ">", 1);
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (check_eof(eof, line) == 0)
			break ;
		ft_putstr_fd(line, tmp_fd);
		free(line);
	}
	free(line);
	close (tmp_fd);
	tmp_fd = open("/tmp/heredoc_pipex", O_RDONLY);
	return (tmp_fd);
}
