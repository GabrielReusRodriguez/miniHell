/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:44:46 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/14 22:31:06 by gabriel          ###   ########.fr       */
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

	if (tokenizer_valida_str(line) == false)
	{
		printf("Syntax error quotes not closed\n");
		return ;
	}
	token_set = tokenizer(line, &shell->cfg.env);
	if (token_set.tokens == NULL)
		return ;
	if (parser_get_cmdset(&token_set, &cmd_set, &shell->cfg.env) == NULL)
		return (tokens_destroy_tokenlist(&token_set));
	i = 0;
	while (i < cmd_set.cmd_count)
	{
        cmd_heredoc(&cmd_set.cmds[i], shell->cfg.env);
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
		if (line == NULL)
			break ;
		if (ft_strlen(line) > 0)
		{
			treat_line(&shell, line);
			//rl_on_new_line();
			add_history(line);
		}
		free(line);
		printf("%d", shell.status.return_status);
	}
	minishell_destroy(shell);
	return (shell.status.return_status);
}
