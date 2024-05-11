/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:15:17 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/11 01:58:49 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PTR_H
# define PTR_H

# include "datatypes.h"

void	    *ptr_free(void *ptr);
void	    *ptr_freematrix(t_string *matrix);
void	    *ptr_freematrix_wsize(t_string *matrix, size_t size);
t_string	*ptr_new_matrix(size_t size);
void        ptr_check_malloc_return(void *ptr, t_string msg);

#endif
