/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:16:41 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/16 10:24:04 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_datatypes.h"

#include <stdio.h>

void *ft_ptr_freeptr(void *ptr)
{
	free (ptr);
	return (NULL);
}

void *ft_ptr_freematrix(t_string *matrix)
{
	size_t	i;

	if(matrix != NULL)
	{
		i = 0;
		while (matrix[i] != NULL)
		{
			printf("Valor 1\n");
			free(matrix[i]);
			printf("Valor 2\n");
			i++;
		}
		printf("Valor\n");
		free(matrix);
	}
	return (NULL);
}

void *ft_ptr_freematrix_wsize(t_string *matrix, size_t size)
{
	size_t	i;

	if (matrix != NULL)
	{
		i = 0;
		while (i < size)
		{
			if (matrix[i] != NULL)
				free(matrix[i]);
			i++;
		}
		free (matrix);
	}
	return (NULL);
}