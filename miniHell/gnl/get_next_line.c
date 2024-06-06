/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:54:34 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/29 22:21:36 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*clean_static_buffer(char *static_buffer)
{
	char	*new_buffer;
	char	*ptr;
	int		len;

	ptr = gnl_strchr(static_buffer, '\n');
	if (!ptr)
		return (ft_free(&static_buffer));
	else
		len = (ptr - static_buffer) + 1;
	if (!static_buffer[len])
		return (ft_free(&static_buffer));
	new_buffer = gnl_substr(static_buffer, len, gnl_strlen(static_buffer)
			- len);
	ft_free(&static_buffer);
	return (new_buffer);
}

char	*new_line(char *static_buffer)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = gnl_strchr(static_buffer, '\n');
	len = (ptr - static_buffer -1) + 1;
	line = gnl_substr(static_buffer, 0, len);
	return (line);
}

char	*read_file(int fd, char *static_buffer)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(&static_buffer));
	buffer[0] = '\0';
	while (bytes_read > 0 && !gnl_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			static_buffer = gnl_strjoin(static_buffer, buffer);
		}
	}
	free(buffer);
	if (bytes_read == -1)
		return (ft_free(&static_buffer));
	return (static_buffer);
}

char	*get_next_line(int fd)
{
	static char	*static_buffer;
	char		*line;

	if (fd < 0)
		return (NULL);
	if ((static_buffer && !gnl_strchr(static_buffer, '\n')) || !static_buffer)
		static_buffer = read_file(fd, static_buffer);
	if (!static_buffer)
		return (NULL);
	line = new_line(static_buffer);
	if (!line)
		return (ft_free(&static_buffer));
	static_buffer = clean_static_buffer(static_buffer);
	return (line);
}
