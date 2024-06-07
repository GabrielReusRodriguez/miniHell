/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:42:50 by abluis-m          #+#    #+#             */
/*   Updated: 2024/06/07 23:22:38 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"
#include "libft.h"
#include "get_next_line.h"
#include "ptr.h"

char	*build_cmd_line(char **vector, int argc)
{
	int			i;
	t_string	line;
	t_string	aux;

	if (argc != 3 || ft_strcmp("-c", vector[1]) != 0)
	{
		ft_putendl_fd("Error reading params", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	i = 2;
	line = ft_strdup(vector[i]);
	ptr_check_malloc_return(line, "Error at memory malloc.");
	while (vector[++i])
	{
		aux = line;
		line = gnl_strjoin(aux, " ");
		free (aux);
		ptr_check_malloc_return(line, "Error at memory malloc.");
		aux = line;
		line = gnl_strjoin(aux, vector[i]);
		free (aux);
		ptr_check_malloc_return(line, "Error at memory malloc.");
	}
	return (line);
}
