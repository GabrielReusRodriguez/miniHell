/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:00:22 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/15 22:16:57 by greus-ro         ###   ########.fr       */
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
