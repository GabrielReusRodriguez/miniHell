/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:44:46 by abluis-m          #+#    #+#             */
/*   Updated: 2024/04/23 23:32:26 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"
#include "get_next_line.h"
#include "minishell.h"
#include "builtin.h"
#include "tokens.h"

void	treat_line(t_minishell *shell, t_string line)
{
	t_token_set token_set;

	token_set = ft_tokenizer(line);
	if (ft_strcmp(line, BUILTIN_EXIT) == 0)
		builtin_exit(shell);
	ft_tokens_destroy_tokenlist(&token_set);
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell = minishell_new(env);
	while (1)
	{
		line = readline(MINISHELL_PROMPT);
		//TODO: print error message
		if (line == NULL)
			break ;
		//TODO: cambiar strlen por strisempty
		if (ft_strlen(line) > 0)
		{
			treat_line(&shell, line);
			//rl_on_new_line();
			add_history(line);
			//Aqui va el tokenizer, procesado, balblablabla...
		}
		free(line);
	}
	return (EXIT_SUCCESS);
}
