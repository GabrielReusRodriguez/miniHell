/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:58:10 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/11 15:55:10 by greus-ro         ###   ########.fr       */
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

t_path	ft_path_getpath(void);
void	ft_path_debug(t_path path);

 #endif
 