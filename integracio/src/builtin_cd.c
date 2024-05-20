/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:58:57 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/21 00:20:43 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"
#include "path.h"
#include "error_handler.h"

#include <stdio.h>
/*
if there is no args, then we do cd ~
*/
int	builtin_cd(t_minishell *shell, t_cmd cmd)
{
	t_string	destiny;
	
	if (cmd.args == NULL)
	{
		path_chdir("~", shell);
		return (EXIT_SUCCESS);
	}
	else
	{
		destiny = ((t_token *)cmd.args->content)->value;
		path_chdir(destiny, shell);
	}
	return (EXIT_SUCCESS);
}
