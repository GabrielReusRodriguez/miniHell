/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:06:30 by greus-ro          #+#    #+#             */
/*   Updated: 2024/06/04 22:23:00 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>
#include "signal_handler.h"

/*
Ctrl-C (in older Unixes, DEL) sends an INT signal ("interrupt", SIGINT); 
			by default, this causes the process to terminate.
Ctrl-Z sends a TSTP signal ("terminal stop", SIGTSTP); by default, 
			this causes the process to suspend execution.[4]
Ctrl-\ sends a QUIT signal (SIGQUIT); by default, 
			this causes the process to terminate and dump core.
		it can be done with control + altgr + slash
Ctrl-D sends an EOF.
*/

static void	signal_interactive_mode_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDERR_FILENO, "\n", 1);
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
	Function to set the function that handles the signal.
*/
static	void	signal_setsignal(int signum, void (*handler)(int) )
{
	if (signal(signum, handler) == SIG_ERR)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

static void	signal_heredoc_mode_handler(int sig)
{
	if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		write(STDERR_FILENO, "\n", 1);
	}
}

/*
	YASFTAN
	Yet Another Stupid Function To Avoid Norminette.
*/
static void	signal_heredoc_mode(void)
{
	signal_setsignal(SIGINT, signal_heredoc_mode_handler);
}

/*
       SIG_DFL is a MACRO with the default handler.
	   SIG_IGNL is a MACRO with the ignore signal.
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
		signal_setsignal(SIGINT, SIG_IGN);
		signal_setsignal(SIGQUIT, SIG_IGN);
		signal_setsignal(SIGTERM, SIG_IGN);
		return ;
	}
	if (mode == SIGNAL_MODE_HEREDOC)
		signal_heredoc_mode();
}
