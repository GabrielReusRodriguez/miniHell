/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:15:15 by greus-ro          #+#    #+#             */
/*   Updated: 2024/06/04 22:22:45 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>

#include "minishell.h"
#include "cmd.h"

/*
in ash, zsh, pdksh, bash, the Bourne shell, $? is 128 + n. What that means is 
	that in those shells, if you get a $? of 129, you don't know whether it's 
	because the process exited with exit(129) or whether it was killed by the 
	signal 1 (HUP on most systems). But the rationale is that shells, when they
	do exit themselves, by default return the exit status of the last exited 
	command. By making sure $? is never greater than 255, that allows to have 
	a consistent exit status:

https://unix.stackexchange.com/questions/99112/default-exit-code-when-process\
	-is-terminated
*/
static int	runner_determine_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFSTOPPED(status))
		return (128 + WSTOPSIG(status));
	return (status);
}

/*
	Nos quedamos con el status del mayor pid ya que el pid
	es positivo e incremental.
*/
void	runner_get_status(t_minishell *shell, t_cmd_set *cmd_set)
{
	pid_t	pid;
	pid_t	greater_pid;
	size_t	i;
	int		status;

	if (shell->status.return_status >= 0)
		return ;
	greater_pid = 0;
	i = 0;
	while (i < cmd_set->cmd_count)
	{
		pid = wait(&status);
		if (pid > greater_pid)
		{
			shell->status.return_status = status;
			greater_pid = pid;
		}
		i++;
	}
	shell->status.return_status = runner_determine_status(\
			shell->status.return_status);
}
