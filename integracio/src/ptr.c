/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:16:41 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/11 01:58:41 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"
#include "error_handler.h"

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

void	ptr_check_malloc_return(void *ptr, t_string msg)
{
	if (ptr == NULL)
		error_system_crash(msg);
}