/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:16:41 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/01 18:35:11 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"

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
			free(matrix[i]);
			i++;
		}
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


t_string    *ptr_new_matrix(size_t size)
{
	t_string    *matrix;
	size_t		i;

	matrix = (t_string *)malloc((size + 1)*sizeof(t_string));
	if (matrix == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		matrix[i] = NULL;
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}