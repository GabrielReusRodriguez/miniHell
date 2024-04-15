/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:33:16 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/15 14:03:53 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIGNAL_H
# define FT_SIGNAL_H

# include <signal.h>

typedef int t_signal;

/*
	This is the unique global var. Extern is to make it avaible in other
	files.
	https://en.wikipedia.org/wiki/Volatile_(computer_programming)
	volatile Marks the variable as the variable can change outside the standard 
	flow of code so the compiler has to perform every read and wrie to 
	the var as indicated by the code.
*/
//extern t_signal	last_signal_rcvd;
//extern sig_atomic_t last_signal_rcvd;

/*
	Signals are a positive int so... we can mark NO_SIGNAL as -1
*/
# define NO_SIGNAL -1
/*
	signals...
	Control c -> SIGINT
	Control \ -> SIGQUIT

	However, it is true to say that Ctrl+D signals an End of Transmission (EOT) event which will generally cause a program reading input to close the input file descriptor.
*/
void	ft_signal_init(void);
int		ft_signal_sigint_handler(int signal);
int		ft_signal_sigquit_handler(int signal);
t_signal	ft_signal_getlastsignal(void);

#endif