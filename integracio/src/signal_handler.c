/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:06:30 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/23 17:08:02 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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
		//rl_replace_line("", 0);
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

/*
       SGL_DFL is a MACRO with the default handler.
*/
void	signal_set_mode(int mode)
{
	if (mode == SIGNAL_MODE_INTERACTIVE)
	{
		signal(SIGINT, signal_interactive_mode_handler);
		signal(SIGQUIT, signal_interactive_mode_handler);
		signal(SIGTERM, signal_interactive_mode_handler);
		return ;
	}
	if (mode == SIGNAL_MODE_DEFAULT)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		return ;
	}
	if (mode == SIGNAL_MODE_NOOP)
	{
		signal(SIGINT, signal_noop_handler);
		signal(SIGQUIT, signal_noop_handler);
		signal(SIGTERM, signal_noop_handler);
		return ;
	}
}
