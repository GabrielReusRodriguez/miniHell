/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:08:27 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/23 23:39:55 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include <signal.h>

//typedef int t_signal;

//https://en.wikipedia.org/wiki/Process_group
//La idea seria hacer un kill y enviar la señal al grupo cuando ejecutemos.
//https://stackoverflow.com/questions/42430023/unix-childs-process-group-id

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

# define SIGNAL_MODE_INTERACTIVE 0
# define SIGNAL_MODE_DEFAULT 2
# define SIGNAL_MODE_NOOP 3

/*
	Signals are a positive int so... we can mark NO_SIGNAL as -1
*/
# define NO_SIGNAL -1
/*
	signals...
	Control c -> SIGINT
	Control \ -> SIGQUIT

	However, it is true to say that Ctrl+D signals an End of Transmission 
    (EOT) event which will generally cause a program reading input to close 
    the input file descriptor.
*/

void		signal_parent_handler(int signal);
void		signal_child_handler(int signal);
void		signal_set_signal_mode(int mode);

/*
Ejemplo:

void	wait_signal(int i)
{
	struct sigaction	sa;

	if (i)
		sa.sa_handler = &signal_handler;
	else
		sa.sa_handler = &child_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
*/

#endif
