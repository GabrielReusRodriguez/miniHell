/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:15:17 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/01 18:38:44 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PTR_H
# define PTR_H

# include "datatypes.h"

void		*ptr_free(void *ptr);
void		*ptr_freematrix(t_string *matrix);
void		*ptr_freematrix_wsize(t_string *matrix, size_t size);
t_string	*ptr_new_matrix(size_t size);

#endif
