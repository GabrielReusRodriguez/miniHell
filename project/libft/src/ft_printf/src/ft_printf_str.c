/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:09:17 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/10 19:17:55 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

#include "libft.h"

int	ft_printf_fd_str(va_list argp, int fd)
{
	char	*str;

	str = va_arg(argp, char *);
	if (str == NULL)
		return (ft_iputstr_fd("(null)", fd));
	else
		return (ft_iputstr_fd(str, fd));
}

int	ft_printf_str(va_list argp)
{
	return (ft_printf_fd_str(argp, STDOUT_FILENO));
}
