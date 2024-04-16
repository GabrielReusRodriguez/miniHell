/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:18:50 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/15 21:57:39 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdio.h>

#include <signal.h>
#include "ft_signal.h"
#include "ft_minishell.h"
/*
Generic signal help
https://www.geeksforgeeks.org/signals-c-language/
https://en.wikipedia.org/wiki/C_signal_handling
*/
//sig_atomic_t	last_signal_rcvd;
extern t_signal	last_signal_rcvd;

/*
Help about control +D
https://stackoverflow.com/questions/1516122/how-to-capture-controld-signal 
tal vez se pueda gestionar haciendo el cambiazo en el terminal y pasandolo smo SIGUSR1
10 SIGUSR1 Left for the programmers to do whatever they want.
*/

/*
	Cuando estamos en modo "Entrada de texto" hay que interceptar la señal y 
	que se comporte como toca. En entrada de texto, Control + C hace nueva linea... 
	si ejecuta un proceso lo mata...
*/

/*
https://stackoverflow.com/questions/231912/what-is-the-difference-between-sigaction-and-signal
Nota: Segun he leido, recomiendan usar signaction ya que signal lo consideran anticuado. Ademas
sigaction contiene más control con los flags del struct sigaction.
*/

//https://github.com/carce-bo42/42_minishell 

/*
Para la señal sigint en el modo input 
	1. Vaciamos la linea
	2. Pintamos el salto de linea
	3. Informamos a readline que tenemos nueva linea
	4. Volvemos a mostrar lo que conteiene le buffer.
*/
void	ft_signal_sigint_input_handler(int signal)
{
	(void)signal;
	last_signal_rcvd = SIGINT;
	/*
	rl_replace_line("",0);
	rl_redisplay();
	printf("\n%s",MINISHELL_PROMPT);
	*/

	//rl_replace_line("",0);
	//rl_redisplay();
	//rl_replace_line("",0);
	//rl_redisplay();
	/*
	printf("\n");
	rl_on_new_line();
	rl_replace_line("",0);
	rl_redisplay();
	*/
	rl_replace_line("",0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();

}

void	ft_signal_sigquit_input_handler(int signal)
{
	(void)signal;
	last_signal_rcvd = SIGQUIT;
	printf("SIGQUIT\n");	
}

void	ft_signal_inputmode(void)
{
	last_signal_rcvd = NO_SIGNAL;
	signal(SIGINT, ft_signal_sigint_input_handler);
	signal(SIGQUIT, ft_signal_sigquit_input_handler);
}


