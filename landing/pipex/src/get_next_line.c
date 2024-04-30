/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 00:03:10 by abluis-m          #+#    #+#             */
/*   Updated: 2024/02/07 11:43:45 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*clean_data(char *data)
{
	char	*new_data;
	char	*end;
	int		len;

	end = ft_strchr(data, '\n');
	if (!end)
		return (ft_free(&data));
	else
		len = (end - data) + 1;
	if (!data[len])
		return (ft_free(&data));
	new_data = gnl_substr(data, len, ft_strlen(data) - len);
	ft_free(&data);
	return (new_data);
}

char	*new_line(char *data)
{
	char	*line;
	char	*end;
	int		len;

	end = ft_strchr(data, '\n');
	len = (end - data) + 1;
	line = gnl_substr(data, 0, len);
	return (line);
}

char	*read_file(int fd, char *data)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(&data));
	buffer[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			data = gnl_strjoin(data, buffer);
		}
	}
	free(buffer);
	if (bytes_read == EOF)
		return (ft_free(&data));
	return (data);
}

char	*get_next_line(int fd)
{
	static char	*data;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((data && !ft_strchr(data, '\n')) || !data)
		data = read_file(fd, data);
	if (!data)
		return (NULL);
	line = new_line(data);
	if (!line)
		return (ft_free(&data));
	data = clean_data(data);
	return (line);
}
