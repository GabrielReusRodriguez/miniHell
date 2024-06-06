/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:35:18 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/29 09:56:20 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_H
# define FD_H

# include "datatypes.h"

/*
	fd.c
*/
void	fd_close(int fd);
int		fd_open_file_truncate(t_string file);
int		fd_open_file_append(t_string file);

#endif