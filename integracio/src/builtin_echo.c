/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:39 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/04 13:55:52 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"
#include <stdio.h>

bool	check_nflag(t_cmd cmd)
{
	t_list	*node;
	t_token	*token;

	if (cmd.args == NULL)
		return (false);
	node = cmd.args;
	token = (t_token *)node->content;
	if (ft_strcmp(token->value, "-n") == 0)
		return (true);
	return (false);
}

int	builtin_echo(t_cmd cmd)
{
	t_list	*node;
	t_token	*token;
	bool	nflag;
	int		out;

	out = STDOUT_FILENO;
	nflag = check_nflag(cmd);
	node = cmd.args;
	if (nflag)
		node = node->next;
	while (node != NULL)
	{
		token = (t_token *)node->content;
		ft_putstr_fd(token->value, out);
		if (node->next)
			ft_putchar_fd(' ', out);
		node = node->next;
	}
	if (!nflag)
		ft_putchar_fd('\n', out);
	return (EXIT_SUCCESS);
}
