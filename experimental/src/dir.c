/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:09:59 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/31 01:04:23 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int	is_dir(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	return (S_ISDIR(path_stat.st_mode));
}
