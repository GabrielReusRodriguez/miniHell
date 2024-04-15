/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 22:23:45 by gabriel           #+#    #+#             */
/*   Updated: 2024/04/15 17:02:42 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
	Como no acepta parámetros y lo escriben por minishell, considero
	que siempre será salir con exito ok.
*/
void    ft_cmd_exit(void)
{
	exit(EXIT_SUCCESS);
}