/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:44:46 by abluis-m          #+#    #+#             */
/*   Updated: 2024/04/19 08:12:22 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>

#include "minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		signal_set_mode(SIGNAL_MODE_INTERACTIVE);
		line = readline(MINISHELL_PROMPT);
		//TODO: print error message
		if (line == NULL)
			break ;
		//TODO: cambiar strlen por strisempty
		if (ft_strlen(line) > 0)
		{
			//rl_on_new_line();
			add_history(line);
			//Aqui va el tokenizer, procesado, balblablabla...
		}
		free(line);
	}
	return (EXIT_SUCCESS);
}
