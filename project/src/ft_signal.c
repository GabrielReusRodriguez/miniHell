/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:18:50 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/15 13:41:45 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_signal.h"

/*
Generic signal help
https://www.geeksforgeeks.org/signals-c-language/
https://en.wikipedia.org/wiki/C_signal_handling
*/

/*
Help about control +D
https://stackoverflow.com/questions/1516122/how-to-capture-controld-signal 
tal vez se pueda gestionar haciendo el cambiazo en el terminal y pasandolo smo SIGUSR1
10 SIGUSR1 Left for the programmers to do whatever they want.
*/

//sig_atomic_t	last_signal_rcvd;
t_signal	last_signal_rcvd;

void	ft_signal_sigint_handler(int signal)
{
	last_signal_rcvd = SIGINT;
}

void	ft_signal_sigquit_handler(int signal)
{
	last_signal_rcvd = SIGQUIT;
}

void	ft_signal_init(void)
{
	last_signal_rcvd = NO_SIGNAL;
	signal(SIGINT, ft_signal_sigint_handler);
	signal(SIGQUIT, ft_signal_sigquit_handler);
}

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

