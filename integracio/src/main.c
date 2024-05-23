/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:44:46 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/23 18:30:34 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>

#include "datatypes.h"
#include "libft.h"
#include "minishell.h"
#include "tokens.h"
#include "parser.h"
#include "cmd.h"
#include "tokens.h"

static bool	is_empty_line(t_string line)
{
	size_t	i;

	if (ft_strlen(line) == 0)
		return (true);
	i = 0;
	while (line[i] != '\0')
	{
		if (tokenizer_charinset(line[i], TOKENS_SEPARATORS) == false)
			return (false);
		i++;
	}
	return (true);
}

static void	treat_line(t_minishell *shell, t_string line)
{
	t_token_set	token_set;
	t_cmd_set	cmd_set;
	size_t		i;

	if (tokenizer_valida_str(line) == false)
	{
		ft_putendl_fd("Syntax error quotes not closed\n", STDERR_FILENO);
		return ;
	}
	token_set = tokenizer(line, *shell);
	if (token_set.tokens == NULL)
		return ;
	if (parser_get_cmdset(&token_set, &cmd_set) == NULL)
		return (tokens_destroy_tokenlist(&token_set));
	i = 0;
	while (i < cmd_set.cmd_count)
	{
		cmd_heredoc(&cmd_set.cmds[i], *shell);
		cmd_debug(cmd_set.cmds[i]);
		i++;
	}
	cmd_set_run(shell, cmd_set);
	tokens_destroy_tokenlist(&token_set);
	cmd_destroy_set(&cmd_set);
}

static void	main_loop(t_minishell *shell)
{
	t_string	line;
	t_string	prompt;		

	while (shell->status.run == true)
	{
		signal_set_mode(SIGNAL_MODE_INTERACTIVE);
		prompt = minishell_get_prompt();
		line = readline(prompt);
		if (line == NULL)
			break ;
		if (is_empty_line(line) == false)
		{
			treat_line(shell, line);
			//rl_on_new_line();
			add_history(line);
		}
		free(line);
		free(prompt);
		printf("%d", shell->status.return_status);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell = minishell_new(env);
	main_loop(&shell);
	minishell_destroy(shell);
	//rl_clear_history();
	return (shell.status.return_status);
}
