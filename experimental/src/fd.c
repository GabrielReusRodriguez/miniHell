/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:37:00 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/29 09:56:56 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "datatypes.h"
#include "redirect.h"

void	fd_close(int fd)
{
	if (fd >= 0)
		close (fd);
}

int	fd_open_file_truncate(t_string file)
{
	int	result;

	result = open(file, O_WRONLY | O_CREAT, \
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	return (result);
}

int	fd_open_file_append(t_string file)
{
	int	result;

	result = open(file, \
					O_WRONLY | O_APPEND | O_CREAT, \
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	return (result);
}
