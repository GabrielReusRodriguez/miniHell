/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:15:17 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/11 15:53:39 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_PTR_H
# define FT_PTR_H

# include "ft_datatypes.h"

void *ft_ptr_freeptr(void *ptr);
void *ft_ptr_freematrix(t_string *matrix);
void *ft_ptr_freematrix_wsize(t_string *matrix, size_t size);

#endif