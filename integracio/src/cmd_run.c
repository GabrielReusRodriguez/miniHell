/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:00:30 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/26 19:33:58 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <sys/errno.h>
#include <sys/wait.h>

#include "cmd.h"
#include "ptr.h"
#include "path.h"
#include "perm.h"
#include "builtin.h"
#include "error_handler.h"

int set_heredoc(char *redir)
{
	(void)redir;
	return (0);
}

t_string *cmd_full(t_cmd cmd)
{
	t_string    *argv;
	size_t      total;
	size_t      i;
	t_list      *head;

	total = ft_lstsize(cmd.args) + 2;
	argv = safe_malloc(sizeof(t_string) * total);
	i = 0;
	head = cmd.args;
	argv[i++] = cmd.exec->value;
	while (head)
	{
		argv[i] = ((t_token *)head->content)->value;
		i++;
		head = head->next;
	}
	argv[i] = NULL;
	return (argv);

}

t_string    cmd_path(char **paths, t_string command)
{
	char    *temp;
	char    *cmd;

	if (!path_isrelative(command))
		return (command);
	else if (access(command, F_OK) == 0)
		return (command);
	while(*paths)
	{
		temp = ft_strjoin(*paths, "/");
		cmd = ft_strjoin(temp, command);
		free(temp);
//      printf("%s\n", cmd);
		if (access(cmd, F_OK) == 0)
			return (cmd);
		free (cmd);
		paths++;
	}
	return (NULL);
}

int get_exit_status(t_cmd_set *cmd_set, pid_t *pids)
{
	size_t  i;
	int status;

	i = 0;
	while(i < cmd_set->cmd_count)
		waitpid(pids[i++], &status, 0);
	free(pids);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			return (130);
		else if (WTERMSIG(status) == SIGQUIT)
			return (131);
	}
	return (0);
}

void    child_process(t_minishell *shell, t_cmd cmd, char **paths)
{
	char	*path;
	char	**full_cmd;
	char	**env;

	//close(cmd.pipe[0]);
	//dup2(cmd.pipe[0], STDIN_FILENO);
	//dup2(cmd.pipe[1], STDIN_FILENO);
	//close(cmd.pipe[1]);
	printf("Prepare exec for %s\n", cmd.exec->value);
	path = cmd_path(paths, cmd.exec->value);
	if (!path)
		ft_error(NO_COMMAND, cmd.exec->value);
	//printf("Path: %s\n", path);
	full_cmd = cmd_full(cmd);
//	full_cmd = safe_malloc(sizeof(char *) * 3);
//	full_cmd[0] = ft_strdup(cmd.exec->value);
//	full_cmd[1] = ft_strdup(((t_token *)cmd.args->content)->value);
//	full_cmd[2] = NULL;
//	vector_debug(full_cmd);
	env = env_to_vector(shell->cfg.env);
	//vector_debug(env);
	execve(path, full_cmd, env);
	printf("After execve");
}

void    init_fd(t_cmd cmd, int *fds)
{
	(void)cmd;
	(void)fds;
/*  
	if (cmd.red_in && cmd.red_in->type == TOKEN_TYPE_RED_HERE_DOC)
	{
		if (cmd.red_in_origin != NULL)
			cmd.pipe[0] = set_heredoc(cmd.red_in_origin->value);
	}
	else if (cmd.red_in && cmd.red_in->type == TOKEN_TYPE_RED_INPUT)
		cmd.pipe[0] = open(cmd.red_in_origin->value, O_RDONLY);
	else
		cmd.pipe[0] = STDIN_FILENO;
	if (cmd.red_out && cmd.red_out->type == TOKEN_TYPE_RED_TRUNCATE)
		cmd.pipe[1] = open(cmd.red_out_dest->value, O_RDWR | O_CREAT | O_TRUNC,
				0644);
	else if (cmd.red_out && cmd.red_out->type == TOKEN_TYPE_RED_APPEND)
		cmd.pipe[1] = open(cmd.red_out_dest->value, O_RDWR | O_CREAT | O_APPEND,
				420);
	else
		cmd.pipe[1] = STDOUT_FILENO;*/
}


int cmd_run(t_minishell *shell, t_cmd cmd)
{
	int     code;

	code = 0;
	if (cmd_isbuiltin(cmd))
		code = builtin_run(shell, cmd, false);
	return (code);
/*  
	init_fd(cmd);
	cmd.paths = ft_split(get_en_var("PATH", envp), ':');
	close_pipes(cmd);
*/
}

int run_pipex(t_minishell *shell, t_cmd_set *cmd_set, t_string *paths)
{
	pid_t	*pids;
	size_t	i;
	int		status;

	i = 0;
	pids = safe_malloc(sizeof(pid_t) * (cmd_set->cmd_count));
	while (i < cmd_set->cmd_count)
	{
		pipe(cmd_set->cmds[i].pipe);
		printf("Forking for %s\n", cmd_set->cmds[i].exec->value);
		pids[i] = fork();
		if (pids[i] < 0)
			ft_error(errno, NULL);
		else if (pids[i] == 0)
			child_process(shell, cmd_set->cmds[i], paths);
		i++;
	}
	status = get_exit_status(cmd_set, pids);
	return(status);
}

int cmd_set_run(t_minishell *shell, t_cmd_set *cmd_set)
{
	int			code;
	t_string	*paths;
//	size_t		i;

	code = 0;
	paths = ft_split(((env_get_var(shell->cfg.env,"PATH"))->value), ':');
//	i = 0;
	if (cmd_set->cmd_count == 1 && cmd_isbuiltin(cmd_set->cmds[0]))
		code = builtin_run(shell, cmd_set->cmds[0], true);
	else
		code = run_pipex(shell, cmd_set, paths);
	return (code);
}
