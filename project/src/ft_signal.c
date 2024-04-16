/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:31:44 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/15 21:32:58 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signal.h"

//sig_atomic_t	last_signal_rcvd;
t_signal	last_signal_rcvd;

/*
With this function we get sure that we get the value and reset the global valaue
*/
t_signal	ft_signal_getlastsignal(void)
{
	t_signal	value;

	value = last_signal_rcvd;
	last_signal_rcvd = NO_SIGNAL;
	return (value);
}
