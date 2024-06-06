/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:42:50 by abluis-m          #+#    #+#             */
/*   Updated: 2024/06/06 18:24:08 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"
#include "libft.h"
#include "get_next_line.h"

char	*build_cmd_line(char **vector)
{
	int			i;
	t_string	line;

	i = 1;
	line = ft_strdup(vector[i]);
	//check strdup malloc
	while (vector[++i])
	{
		line = gnl_strjoin(line, " ");
		//check strjoin malloc
		line = gnl_strjoin(line, vector[i]);
		//check strjoin malloc
	}
	return (line);
}
