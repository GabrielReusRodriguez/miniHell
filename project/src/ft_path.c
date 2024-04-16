/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:00:02 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/16 08:21:14 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "ft_environment.h"
#include "ft_path.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_ptr.h"

/*
Pendiente anyadir el tamanyo de las carpetas en path ya que si hay que hacer un free matrix, 
hayq ue pasarle el argumento xq si no solo se hara free hasta el punto que estemos.
*/
static t_string	*ft_path_normalize(t_string *folders, size_t size)
{
	t_string	aux;
	size_t		i;

	i = 0;
	while(folders[i] != NULL)
	{
		aux = folders[i];
		folders[i] = ft_strjoin(folders[i], "/");
		if (folders[i] == NULL)
		{
			ft_ptr_freematrix_wsize(folders, size);
			return (NULL);
		}
		free (aux);
		i++;
	}
	return (folders);
}

static size_t	ft_path_numfolders(t_string *folder)
{
	size_t	size;
	
	size = 0;
	if (folder == NULL)
		return (size);
	while(folder[size] != NULL)
		size++;
	return (size);
}

t_path	ft_path_getpath(t_string str_path)
{
	t_path	path;

	if (str_path == NULL)
	{
		path.folders = NULL;
		path.total = 0;
		return (path);
	}
	path.folders = ft_split(str_path, ':');
	if (path.folders == NULL)
		return (path);
	path.total = ft_path_numfolders(path.folders);
	path.folders = ft_path_normalize(path.folders, path.total);
	return (path);
}

/*
t_path	ft_path_getpath(t_string str_path);
{
	t_path		path;
	/t_env_var	env_path;
	
	env_path = ft_env_getenvvar("PATH");
	if (env_path.value == NULL)
	{
		path.folders = NULL;
		return (path);
	}
	path.folders = ft_split(env_path.value, ':');
	if (path.folders == NULL)
	{
		ft_env_freevar(&env_path);
		return (path);
	}
	path.total = ft_path_numfolders(path.folders);
	path.folders = ft_path_normalize(path.folders, path.total);
	ft_env_freevar(&env_path);
	return (path);
}
*/
void	ft_path_debug(t_path path)
{
	size_t	i;

	if (path.folders == NULL)
	{
		ft_printf("PATH is empty\n");
		return ;
	}
	i = 0;
	ft_printf("Path is: \n");
	while (path.folders[i] != NULL)
	{
		ft_printf("\t %s \n", path.folders[i]);
		i++;
	}
	ft_printf("END Path\n");
}

void	ft_path_destroy(t_path *path)
{
	size_t		i;

	i = 0;
	while (path->folders[i] != NULL)
	{
		free (path->folders[i]);
		i++;
	}
	free(path->folders);
	path->folders = NULL;
	path->total = 0;
}
