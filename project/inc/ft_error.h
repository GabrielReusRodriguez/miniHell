/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:41:00 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/10 20:51:20 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include "ft_datatypes.h"

void ft_error_print_msg(t_string msg);
void ft_error_print_errnum(t_string msg, int errnum);
void ft_error_print_errno(void);

#endif