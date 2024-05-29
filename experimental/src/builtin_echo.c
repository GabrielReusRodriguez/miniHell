/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:21:39 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/29 13:37:10 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

static bool	check_nflag(t_cmd cmd)
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
	bool	payload_found;

	payload_found= false;
	nflag = check_nflag(cmd);
	node = cmd.args;
	while (node != NULL)
	{
		token = (t_token *)node->content;
		if (ft_strcmp("-n", token->value) != 0)
			payload_found = true;
		if (payload_found)
		{
			ft_putstr_fd(token->value, STDOUT_FILENO);
			if (node->next)
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		node = node->next;
	}
	if (!nflag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
