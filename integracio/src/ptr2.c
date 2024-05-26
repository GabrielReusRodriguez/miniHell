/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:28:04 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/25 18:24:23 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/errno.h>
#include <stdlib.h>

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		perror("Error at memory malloc");
		exit(errno);
	}
	return (ptr);
}

void	vector_debug(char **vector)
{
	int	i;

	i = 0;
	while (vector[i])
	{
		printf("%s\n", vector[i]);
		i++;
	}
}
