/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_up_hex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:19:46 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/10 19:18:07 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

#include "libft.h"
#include "ft_printf.h"

int	ft_printf_fd_up_hex(va_list argp, int fd)
{
	unsigned int	arg;
	char			*hex_number;

	arg = va_arg(argp, unsigned int);
	hex_number = ft_printf_htoa(arg, 1);
	if (hex_number == NULL)
		return (-1);
	return (ft_iputstr_fd(hex_number, fd));
}

int	ft_printf_up_hex(va_list argp)
{
	return (ft_printf_fd_up_hex(argp, STDOUT_FILENO));
}
