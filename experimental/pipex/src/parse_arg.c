/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 23:31:14 by abluis-m          #+#    #+#             */
/*   Updated: 2024/04/25 14:52:08 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_file_perm(char *fname)
{
	if (access(fname, F_OK) < 0)
		return (NO_FILE);
	else if (access(fname, R_OK) < 0)
		return (NO_READ);
	else if (access(fname, W_OK) < 0)
		return (NO_WRITE);
	return (PERM_OK);
}

int	check_cmd_perm(char *cname)
{
	if (access(cname, F_OK) < 0)
		return (NO_COMMAND);
	else if (access(cname, X_OK) < 0)
		return (NO_EXEC);
	return (PERM_OK);
}

void	free_cmd(t_cmd *cmds, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(cmds[i].path);
		free_tab(cmds[i].arg);
		i++;
	}
}

t_cmd	parse_cmd(char *command, char **paths)
{
	t_cmd	cmd;
	int		i;
	char	*tmp;

	i = 0;
	cmd.arg = ft_split_quotes(command);
	cmd.name = cmd.arg[0];
	if (paths == NULL)
		return (cmd);
	if (access(cmd.arg[0], F_OK) == 0 || command[0] == '.')
	{
		cmd.path = cmd.arg[0];
		return (cmd);
	}
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd.path = ft_strjoin(tmp, cmd.arg[0]);
		free(tmp);
		if (access(cmd.path, F_OK) == 0)
			return (cmd);
		i++;
		free(cmd.path);
	}
	return (cmd);
}

char	*get_env_var(char *name, char **envp)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j ++;
		key = ft_substr(envp[i], 0, j);
		if (ft_strncmp(key, name, ft_strlen(name)) == 0)
		{
			free(key);
			return (envp[i] + j + 1);
		}
		free(key);
		i++;
	}
	return (NULL);
}
