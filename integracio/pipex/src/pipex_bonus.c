/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:53:25 by abluis-m          #+#    #+#             */
/*   Updated: 2024/04/25 15:00:05 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

void	child_process(t_pipex pipex, t_cmd cmd, int *pipes)
{
	close(pipes[0]);
	cmd.perm = check_cmd_perm(cmd.path);
	error_exit(cmd);
	if (cmd.id == 0)
	{
		if (pipex.fd[0].perm != PERM_OK && pipex.fd[0].perm != NO_WRITE)
			ft_error(pipex.fd[0].perm, pipex.fd[0].name);
		dup2(pipex.fd[0].fd, STDIN_FILENO);
	}
	if (cmd.id == pipex.cmd_count -1)
	{
		if (pipex.fd[1].perm != PERM_OK && pipex.fd[1].perm != NO_READ)
			ft_error(pipex.fd[1].perm, pipex.fd[1].name);
		dup2(pipex.fd[1].fd, STDOUT_FILENO);
	}
	else
		dup2(pipes[1], STDOUT_FILENO);
	close(pipes[1]);
	if (execve(cmd.path, cmd.arg, pipex.env) < 0)
		ft_error(errno, cmd.arg[0]);
}

int	get_exit_status(t_pipex pipex, pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipex.cmd_count)
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

void	run_pipex(t_pipex pipex, t_cmd *cmd)
{
	pid_t	*pids;
	int		pipes[2];
	int		std_tmp[2];
	int		i;

	i = 0;
	pids = safe_malloc(sizeof(pid_t) * (pipex.cmd_count));
	dup_tmp(std_tmp, IN);
	while (i < pipex.cmd_count)
	{
		if (pipe(pipes) < 0)
			ft_error(errno, NULL);
		pids[i] = fork();
		if (pids[i] < 0)
			ft_error(errno, NULL);
		else if (pids[i] == 0)
			child_process(pipex, cmd[i], pipes);
		dup2(pipes[0], STDIN_FILENO);
		close (pipes[1]);
		close (pipes[0]);
		i++;
	}
	i = get_exit_status(pipex, pids);
	close_pipes(pipex, std_tmp);
	exit(i);
}

void	init_fd(t_pipex *pipex, char **argv)
{
	char	*infile;
	char	*outfile;

	infile = argv[1];
	outfile = argv[pipex->cmd_count + 2 + pipex->heredoc];
	pipex->fd[0].name = infile;
	pipex->fd[1].name = outfile;
	if (pipex->heredoc)
	{
		pipex->fd[0].fd = set_heredoc(argv[2]);
		pipex->fd[1].fd = open(outfile, O_RDWR | O_CREAT | O_APPEND, 420);
		return ;
	}
	else
	{
		pipex->fd[0].fd = open(infile, O_RDONLY);
		pipex->fd[1].fd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	pipex->fd[0].perm = check_file_perm(infile);
	pipex->fd[1].perm = check_file_perm(outfile);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	char	**paths;
	t_cmd	*cmd;
	int		i;

	if (argc < 5)
		ft_error(ARG_ERROR, NULL);
	pipex.heredoc = (ft_strncmp(argv[1], HERE_DOC, 9) == 0);
	pipex.cmd_count = (argc - 3) - pipex.heredoc;
	init_fd(&pipex, argv);
	paths = ft_split(get_env_var("PATH", envp), ':');
	pipex.env = envp;
	i = 0;
	cmd = safe_malloc(sizeof(*cmd) * (pipex.cmd_count));
	while (i < pipex.cmd_count)
	{
		cmd[i] = parse_cmd(argv[i + 2 + pipex.heredoc], paths);
		cmd[i].id = i;
		i++;
	}
	free_tab(paths);
	run_pipex(pipex, cmd);
	free_cmd(cmd, pipex.cmd_count);
	exit(EXIT_SUCCESS);
}
