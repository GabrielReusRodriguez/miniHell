/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_low_hex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:19:29 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/10 19:16:32 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

#include "ft_printf.h"
#include "libft.h"

int	ft_printf_fd_low_hex(va_list argp, int fd)
{
	unsigned int	arg;
	char			*hex_num;

	arg = va_arg(argp, unsigned int);
	hex_num = ft_printf_htoa(arg, fd);
	if (hex_num == NULL)
		return (-1);
	return (ft_iputstr_fd(hex_num, fd));
}

int	ft_printf_low_hex(va_list argp)
{
	return (ft_printf_fd_low_hex(argp, STDOUT_FILENO));
}
