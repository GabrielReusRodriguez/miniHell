/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:04:23 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/10 19:15:39 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

#include "libft.h"

int	ft_printf_fd_char(va_list argp, int fd)
{
	unsigned char	character;

	character = va_arg(argp, int);
	return (ft_iputchar_fd(character, fd));
}

int	ft_printf_char(va_list argp)
{
	return (ft_printf_fd_char(argp, STDOUT_FILENO));
}
