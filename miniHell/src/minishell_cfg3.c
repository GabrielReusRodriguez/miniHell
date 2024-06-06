/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cfg3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 22:20:56 by gabriel           #+#    #+#             */
/*   Updated: 2024/06/04 21:48:27 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datatypes.h"
#include "minishell.h"
#include "var.h"
#include "ptr.h"
#include "libft.h"

#include <stdio.h>

t_string	*minishell_path_2_vector(t_minishell shell)
{
	t_string	*vector;
	t_string	aux;
	size_t		i;

	if (shell.cfg.var_path == NULL)
		return (NULL);
	vector = ft_split(shell.cfg.var_path->value, ':');
	ptr_check_malloc_return(vector, "Error at memory malloc.\n");
	i = 0;
	while (vector[i] != NULL)
	{
		aux = vector[i];
		vector[i] = ft_strjoin(vector[i], "/");
		ptr_check_malloc_return(vector[i], "Error at memory malloc.\n");
		free (aux);
		i++;
	}
	return (vector);
}
