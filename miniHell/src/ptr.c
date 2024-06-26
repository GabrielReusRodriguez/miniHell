/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:16:41 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/23 18:54:45 by gabriel          ###   ########.fr       */
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

void	ptr_check_malloc_return(void *ptr, t_string msg)
{
	if (ptr == NULL)
		error_system_crash(msg);
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

t_string	*ptr_new_matrix(size_t size)
{
	t_string	*matrix;
	size_t		i;

	matrix = (t_string *)malloc((size + 1) * sizeof(t_string));
	ptr_check_malloc_return(matrix, "Error at memory malloc.\n");
	i = 0;
	while (i < size)
	{
		matrix[i] = NULL;
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}
