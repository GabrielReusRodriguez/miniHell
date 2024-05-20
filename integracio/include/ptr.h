/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:15:17 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/20 21:27:48 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PTR_H
# define PTR_H

# include "datatypes.h"

/*
    ptr.c
*/
void		*ptr_free(void *ptr);
void		*ptr_freematrix(t_string *matrix);
void		*ptr_freematrix_wsize(t_string *matrix, size_t size);
t_string	*ptr_new_matrix(size_t size);
void		ptr_check_malloc_return(void *ptr, t_string msg);

/*
    ptr2.c
*/
void		*safe_malloc(size_t size);
void		vector_debug(char **vector);


#endif
