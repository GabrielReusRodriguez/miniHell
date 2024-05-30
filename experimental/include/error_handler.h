/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:14:00 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/31 00:27:15 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

# include "datatypes.h"

# define FORK_ERROR 5
# define DUP_ERROR 4

void	*error_print(t_cstring msg);
void	error_system_crash(t_cstring msg);

#endif