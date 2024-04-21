/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:00:22 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/21 13:33:14 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_builtin.h"
#include "libft.h"

t_bool	ft_builin_isbuiltin(t_string cmd)
{
	if (ft_strcmp(BUILTIN_EXIT, cmd) == 0)
        return (TRUE);
    if (ft_strcmp(BUILTIN_CD, cmd) == 0)
        return (TRUE);
    if (ft_strcmp(BUILTIN_ECHO, cmd) == 0)
        return (TRUE);
    if (ft_strcmp(BUILTIN_ENV, cmd) == 0)
        return (TRUE);
    if (ft_strcmp(BUILTIN_EXPORT, cmd) == 0)
        return (TRUE);
    if (ft_strcmp(BUILTIN_PWD, cmd) == 0)
        return (TRUE);
    if (ft_strcmp(BUILTIN_UNSET, cmd) == 0)
        return (TRUE);
    return (FALSE);
}

