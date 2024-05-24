/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:20:50 by abluis-m          #+#    #+#             */
/*   Updated: 2024/04/25 14:44:09 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"

# define PERM_OK 0
# define NO_FILE 400
# define NO_READ 404
# define NO_WRITE 402
# define NO_EXEC 126
# define NO_COMMAND 127

# define IN 1
# define OUT 0

# define TRUE 1
# define FALSE 0

# define HERE_DOC "here_doc"
# define ARG_ERROR 1

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

typedef struct s_command
{
	char	*path;
	char	**arg;
	char	*name;
	int		perm;
	int		id;
}	t_cmd;

typedef struct s_fd
{
	int		fd;
	char	*name;
	int		perm;
}	t_fd;

typedef struct s_pipex
{
	int		cmd_count;
	char	**env;
	int		heredoc;
	t_fd	fd[2];
}	t_pipex;

int		ft_error(int error_code, char *msg);
void	error_exit(t_cmd cmd);
void	*safe_malloc(size_t size);
void	close_pipes(t_pipex pipex, int *std_tmp);
void	dup_tmp(int *std_tmp, int flag);
void	*free_tab(char **tab);
int		check_file_perm(char *fname);
int		check_cmd_perm(char *cname);
char	*get_env_var(char *name, char **envp);
t_cmd	parse_cmd(char *command, char **paths);
void	free_cmd(t_cmd *cmds, int count);
char	**ft_split_quotes(const char *s);
int		set_heredoc(char *eof);
void	debug_arg(char **av, char **ev);
void	debug_tab(char **tab, char *msg);
void	debug_str(char *str, char *msg);
void	debug_cmd(t_cmd *command);

#endif
