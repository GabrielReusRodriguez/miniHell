/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:44:46 by abluis-m          #+#    #+#             */
/*   Updated: 2024/06/09 19:08:42 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

#include "datatypes.h"
#include "libft.h"
#include "minishell.h"
#include "tokens.h"
#include "parser.h"
#include "cmd.h"
#include "runner.h"
#include "error_handler.h"
#include "signal_handler.h"

/*
	We check if the read line is an empty one or it is composed only 
	with spaces, tabs...
*/
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

/*
	Here we process the line, it is...
		Tokenize the line  to get the list of tokens
		Parse the line to get the cmd set.
		Read the heredoc for the commands that has it
		Execute the cmds in paralel if they are pipes.
*/
static void	treat_line(t_minishell *shell, t_string line)
{
	t_token_set	token_set;
	t_cmd_set	cmd_set;
	size_t		i;

	if (tokenizer_valida_str(line) == false)
	{
		error_print("Syntax error quotes not closed.\n");
		shell->status.return_status = 127;
		return ;
	}
	token_set = tokenizer(line, *shell);
	if (token_set.tokens == NULL)
		return ;
	if (parser_get_cmdset(&token_set, &cmd_set) == NULL)
	{
		shell->status.return_status = 127;
		return (tokens_destroy_tokenlist(&token_set));
	}
	i = 0;
	signal_set_mode(SIGNAL_MODE_HEREDOC);
	while (i < cmd_set.cmd_count)
		cmd_heredoc(&cmd_set.cmds[i++], *shell);
	shell->status.return_status = runner_run_cmd_set(shell, &cmd_set);
	tokens_destroy_tokenlist(&token_set);
	cmd_destroy_set(&cmd_set);
}

/*
	Here we have the loop logic of minishell, 
		we ask for the line
		we check if it is empty.
		we treat the line ( tokenize + parse+ execute)
		we add to history.
	We use isatty to check that STDIN is bounded to 
the terminal
SYNOPSIS
	   #include <unistd.h>

	   int isatty(int fd);

DESCRIPTION
	   The isatty() function tests whether fd is an open file 
	descriptor referring to a terminal.
*/
static void	main_loop(t_minishell *shell)
{
	t_string	line;
	t_string	prompt;		

	while (shell->status.run == true)
	{
		signal_set_mode(SIGNAL_MODE_INTERACTIVE);
		prompt = minishell_get_prompt();
		if (isatty(STDIN_FILENO) == 1)
		{
			line = readline(prompt);
			if (line == NULL)
			{
				free (prompt);
				break ;
			}
			if (is_empty_line(line) == false)
			{
				treat_line(shell, line);
				add_history(line);
			}
			free(line);
			free(prompt);
		}
	}
}

int	run_argv(char **vector, char **env, int argc)
{
	t_minishell	shell;
	t_string	line;

	shell = minishell_new(env);
	line = build_cmd_line(vector, argc);
	if (is_empty_line(line) == false)
		treat_line(&shell, line);
	free(line);
	minishell_destroy(shell);
	return (shell.status.return_status);
}

/*
	This is the main function of the program. 
	we init the minishell structure , do the main loop of the program
	and we free memory at exit.
*/
int	main(int argc, char **argv, char **env)
{
	t_minishell	shell;

	if (argc != 1 || argv[1])
	{
		exit(run_argv(argv, env, argc));
	}
	shell = minishell_new(env);
	main_loop(&shell);
	minishell_destroy(shell);
	rl_clear_history();
	return (shell.status.return_status);
}
