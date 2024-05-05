/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:44:46 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/04 15:21:42 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"
#include "get_next_line.h"
#include "minishell.h"
#include "builtin.h"
#include "tokens.h"
#include "parser.h"
#include "cmd.h"
#include "environment.h"

void	treat_line(t_minishell *shell, t_string line)
{
	t_token_set	token_set;
	t_cmd_set	cmd_set;
	size_t		i;

	token_set = tokenizer(line);
	if (token_set.tokens == NULL)
		return ;
	if (parser_get_cmdset(&token_set, &cmd_set) == NULL)
	{
		tokens_destroy_tokenlist(&token_set);
		return ;
	}
	i = 0;
	while (i < cmd_set.num_cmds)
	{
		cmd_debug(cmd_set.cmds[i]);
		i++;
	}
	cmd_set_run(shell, cmd_set);
	tokens_destroy_tokenlist(&token_set);
	cmd_destroy_set(&cmd_set);
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell = minishell_new(env);
	while (shell.status.run == true)
	{
		signal_set_mode(SIGNAL_MODE_INTERACTIVE);
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
		printf("%d", shell.status.return_status);
	}
	minishell_destroy(shell);
	return (shell.status.return_status);
}
