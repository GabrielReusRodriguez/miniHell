/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:42:50 by abluis-m          #+#    #+#             */
/*   Updated: 2024/06/09 17:55:02 by greus-ro         ###   ########.fr       */
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
		line = gnl_strjoin(line, " ");
		ptr_check_malloc_return(line, "Error at memory malloc.");
		line = gnl_strjoin(line, vector[i]);
		ptr_check_malloc_return(line, "Error at memory malloc.");
	}
	return (line);
}
