/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:06:30 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/31 00:43:12 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include "signal_handler.h"

/*
Ctrl-C (in older Unixes, DEL) sends an INT signal ("interrupt", SIGINT); 
			by default, this causes the process to terminate.
Ctrl-Z sends a TSTP signal ("terminal stop", SIGTSTP); by default, 
			this causes the process to suspend execution.[4]
Ctrl-\ sends a QUIT signal (SIGQUIT); by default, 
			this causes the process to terminate and dump core.
		it can be done with control + altgr + slash
*/

static void	signal_interactive_mode_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (signal == SIGTERM)
	{
		return ;
	}
}

/*
	We do not do anything.
*/
static void	signal_noop_handler(int signal)
{
	if (signal == SIGINT)
	{
		return ;
	}
	if (signal == SIGQUIT)
	{
		return ;
	}
	if (signal == SIGTERM)
	{
		return ;
	}
}

static	void	signal_setsignal(int signum, __sighandler_t handler)
{
	if (signal(signum, handler) == SIG_ERR)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

/*
       SGL_DFL is a MACRO with the default handler.
*/
void	signal_set_mode(int mode)
{
	if (mode == SIGNAL_MODE_INTERACTIVE)
	{
		signal_setsignal(SIGINT, signal_interactive_mode_handler);
		signal_setsignal(SIGQUIT, signal_interactive_mode_handler);
		signal_setsignal(SIGTERM, signal_interactive_mode_handler);
		return ;
	}
	if (mode == SIGNAL_MODE_DEFAULT)
	{
		signal_setsignal(SIGINT, SIG_DFL);
		signal_setsignal(SIGQUIT, SIG_DFL);
		signal_setsignal(SIGTERM, SIG_DFL);
		return ;
	}
	if (mode == SIGNAL_MODE_NOOP)
	{
		signal_setsignal(SIGINT, signal_noop_handler);
		signal_setsignal(SIGQUIT, signal_noop_handler);
		signal_setsignal(SIGTERM, signal_noop_handler);
		return ;
	}
}
