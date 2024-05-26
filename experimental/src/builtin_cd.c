/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:58:57 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/26 20:06:21 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"
#include "path.h"
#include "error_handler.h"

/*
if there is no args, then we do cd ~
*/
int	builtin_cd(t_minishell *shell, t_cmd cmd)
{
	t_string	destiny;
	size_t		num_args;

	if (cmd.args == NULL)
		shell->status.return_status = path_chdir("~", shell);
	else
	{
		num_args = ft_lstsize(cmd.args);
		if (num_args > 1)
		{
			error_print("Error: Too many arguments.\n");
			shell->status.return_status = 127;
			return (shell->status.return_status);
		}
		destiny = ((t_token *)cmd.args->content)->value;
		shell->status.return_status = path_chdir(destiny, shell);
	}
	return (shell->status.return_status);

}
