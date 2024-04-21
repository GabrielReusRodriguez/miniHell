/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:29:47 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/21 13:36:32 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "ft_datatypes.h"
#include "ft_minishell.h"
#include "libft.h"
#include "ft_builtin.h"
#include "ft_environment.h"
#include "ft_path.h"
#include "ft_tokens.h"
#include "ft_signal.h"
#include "ft_minishell.h"

//https://github.com/StefdeRijk/Minishell/
/*
Tutorial de readline
https://03-jon-perez.gitbook.io/coding-library/c/readline
*/

void	ft_main_treat_line(t_minishell *shell, t_string line)
{
    t_token_set	line_tokens;
    t_cmd       cmd;
    t_token     *exec_token;

    line_tokens = ft_tokens_tokenize(line);
    if (ft_tokens_validate_tokenset(line_tokens) == FALSE)
    {
        printf("ERROR , line with invalid format\n");
        return ;
    }
    while (ft_tokens_has_morecmds(line_tokens) == TRUE)
    {
        cmd = ft_tokens_get_next_comand(&line_tokens);
        exec_token = ft_cmd_get_cmd(cmd);
        if (ft_builin_isbuiltin(exec_token->value) == TRUE)
        {
            if (ft_strcmp(line, BUILTIN_EXIT) == 0)
                ft_builtin_exit(shell);
        }
    }
    ft_token_destroy_tokenlist(&line_tokens);

}

//https://www.gnu.org/software/termutils/manual/termcap-1.3/html_chapter/termcap_2.html
int	main(int argc, char **argv, char **env)
{
	t_string	line;
	t_minishell	shell;
	t_path		path;

    argc++;
    (void)argv;

	shell = ft_minishell_new(env);
	path = ft_path_getpath(shell.cfg.path->value);
	ft_path_debug(path);
	ft_path_destroy(&path);
	while(shell.status.run == TRUE)
	{
	//	ft_signal_inputmode();
		ft_signal_set_signal_mode(SIGNAL_MODE_INTERACTIVE);
		line = readline(MINISHELL_PROMPT);
		if (line == NULL)
			break;
		if(ft_strisempty(line) == FALSE)
		{
   			add_history(line);
			ft_main_treat_line(&shell, line);
		}
		free (line);
	}
	ft_minishell_destroy(shell);
	exit (shell.status.return_status);
}