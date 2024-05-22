/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:28:04 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/22 21:44:18 by gabriel          ###   ########.fr       */
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

void    vector_debug(char **vector)
{
    int i;

    i = 0;
    while (vector[i])
    {
        printf("%s\n", vector[i]);
        i++;
    }
}