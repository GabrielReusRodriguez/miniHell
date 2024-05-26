/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:58:57 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/25 16:11:51 by greus-ro         ###   ########.fr       */
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

	if (cmd.args == NULL)
		return (path_chdir("~", shell));
	else
	{
		destiny = ((t_token *)cmd.args->content)->value;
		return (path_chdir(destiny, shell));
	}
}
