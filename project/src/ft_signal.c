/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:31:44 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/16 22:23:45 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <readline/readline.h>
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


/*
Ctrl-C (in older Unixes, DEL) sends an INT signal ("interrupt", SIGINT); by default, this causes the process to terminate.
Ctrl-Z sends a TSTP signal ("terminal stop", SIGTSTP); by default, this causes the process to suspend execution.[4]
Ctrl-\ sends a QUIT signal (SIGQUIT); by default, this causes the process to terminate and dump core.
*/

void	ft_signal_parent_handler(int signal)
{
	if (signal == SIGINT)
	{
		//printf("SIGINT\n");
		rl_replace_line("",0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (signal == SIGQUIT) //se hace con control + altgr + barra
	{
		//printf("SIGQUIT\n");
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if(signal == SIGTERM)
	{
		//printf("SIGTERM\n");
		return ;
	}
}

void	ft_signal_child_handler(int signal)
{
	if (signal == SIGINT)
	{
		
	}
	if (signal == SIGQUIT)
	{
		
	}
	if(signal == SIGTERM)
	{
		
	}
}
/*
       SA_RESTART
              Provide behavior compatible with BSD signal semantics by  making
              certain  system  calls restartable across signals.  This flag is
              meaningful only when establishing a signal  handler.   See  sig‐
              nal(7) for a discussion of system call restarting.


*/
void	ft_signal_set_signal_mode(int mode)
{
	
	struct sigaction	sa;

	if (mode == SIGNAL_MODE_BASH)
		sa.sa_handler = &ft_signal_parent_handler;
	else
		sa.sa_handler = &ft_signal_child_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}