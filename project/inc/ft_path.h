/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:58:10 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/16 08:16:21 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #ifndef FT_PATH_H
 # define FT_PATH_H

# include "ft_datatypes.h"

typedef struct s_path
{
	t_string	*folders;
	size_t		total;
}	t_path;

t_path	ft_path_getpath(t_string str_path);
void	ft_path_debug(t_path path);
void	ft_path_destroy(t_path *path);

 #endif
 