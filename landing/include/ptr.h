/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:15:17 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/23 18:57:23 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PTR_H
# define PTR_H

# include "datatypes.h"

void	*ptr_free(void *ptr);
void	*ptr_freematrix(t_string *matrix);
void	*ptr_freematrix_wsize(t_string *matrix, size_t size);

#endif
