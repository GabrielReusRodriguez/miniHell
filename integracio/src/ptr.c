/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:16:41 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/23 18:59:19 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"

#include <stdio.h>

void	*ptr_free(void *ptr)
{
	free (ptr);
	return (NULL);
}

void	*ptr_freematrix(t_string *matrix)
{
	size_t	i;

	if (matrix != NULL)
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

void	*ptr_freematrix_wsize(t_string *matrix, size_t size)
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
