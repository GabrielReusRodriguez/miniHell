/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:29:47 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/13 22:26:13 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ft_datatypes.h"
#include "ft_printf.h"
#include "libft.h"
#include "ft_command.h"

#include "ft_environment.h"
#include "ft_path.h"
#include "ft_tokens.h"
#include "ft_command.h"

#define PROMPT "minishell> "

/*
Tutorial de readline
https://03-jon-perez.gitbook.io/coding-library/c/readline
*/

void	ft_main_treat_line(t_string line)
{
	if (ft_strcmp(line, CMD_EXIT) == 0)
        ft_command_exit();
}

//https://www.gnu.org/software/termutils/manual/termcap-1.3/html_chapter/termcap_2.html
int	main(void)
{
	t_string	line;
	t_path		path;
	t_token_set	line_tokens;

/*
	path = ft_env_getenvvar("PATH");
	ft_printf("PATH: %s\n",path.value);
*/
	path = ft_path_getpath();
	ft_path_debug(path);
	while(1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break;
		if(ft_strisempty(line) == FALSE)
		{
			/*
			ft_main_treat_line(line);
			add_history(line);
			ft_printf("La linea entrada es: %s\n", line);
			//rl_on_new_line();
			*/
			ft_main_treat_line(line);
			add_history(line);
			//printf("La linea entrada es: %s\n", line);
			line_tokens = ft_tokens_tokenize(line);
			ft_token_destroy_tokenlist(&line_tokens);
		}
		free (line);
	}	
	return (EXIT_SUCCESS);
}