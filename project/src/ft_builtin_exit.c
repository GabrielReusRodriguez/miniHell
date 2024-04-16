/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:06:42 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/16 08:20:07 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*
	Como no acepta parámetros y lo escriben por minishell, considero
	que siempre será salir con exito ok.
*/
void    ft_builtin_exit(t_minishell *shell)
{
	shell->status.run = FALSE;
}