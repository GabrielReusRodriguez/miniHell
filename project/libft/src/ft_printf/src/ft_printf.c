/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:57:30 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/11 18:38:03 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

#include "libft.h"
#include "ft_printf.h"

static int	ft_print_formated_data(va_list argp, char data_type, int fd)
{
	if (data_type == 'c')
		return (ft_printf_fd_char(argp, fd));
	if (data_type == '%')
		return (ft_printf_fd_percent(fd));
	if (data_type == 's')
		return (ft_printf_fd_str(argp, fd));
	if (data_type == 'd')
		return (ft_printf_fd_dec(argp, fd));
	if (data_type == 'i')
		return (ft_printf_fd_int(argp, fd));
	if (data_type == 'u')
		return (ft_printf_fd_usgn(argp, fd));
	if (data_type == 'p')
		return (ft_printf_fd_ptr(argp, fd));
	if (data_type == 'x')
		return (ft_printf_fd_low_hex(argp, fd));
	if (data_type == 'X')
		return (ft_printf_fd_up_hex(argp, fd));
	return (-1);
}

static int	ft_print_special_char(va_list argp, char data_type, int fd)
{
	return (ft_print_formated_data(argp, data_type, fd));
}

int	ft_printf_fd(int fd, char const *str, ...)
{
	va_list		argp;
	int			num_bytes;
	int			printed_bytes;
	size_t		i;

	num_bytes = 0;
	i = 0;
	va_start(argp, str);
	while (str[i] != '\0')
	{
		if (str[i] != '%')
			printed_bytes = ft_iputchar_fd(str[i], fd);
		else
		{
			i++;
			printed_bytes = ft_print_special_char(argp, str[i], fd);
		}
		if (printed_bytes < 0)
			return (printed_bytes);
		num_bytes = num_bytes + printed_bytes;
		i++;
	}
	va_end(argp);
	return (num_bytes);
}

int	ft_printf(char const *str, ...)
{
	va_list		argp;
	int			num_bytes;
	int			printed_bytes;
	size_t		i;

	num_bytes = 0;
	i = 0;
	va_start(argp, str);
	while (str[i] != '\0')
	{
		if (str[i] != '%')
			printed_bytes = ft_iputchar_fd(str[i], STDOUT_FILENO);
		else
		{
			i++;
			printed_bytes = ft_print_special_char(argp, str[i], STDOUT_FILENO);
		}
		if (printed_bytes < 0)
			return (printed_bytes);
		num_bytes = num_bytes + printed_bytes;
		i++;
	}
	va_end(argp);
	return (num_bytes);
}

/*
int	ft_printf_fd(int fd, char const *str, ...)
{
	va_list		argp;
	int			num_bytes;
	int			printed_bytes;
	size_t		i;

	num_bytes = 0;
	i = 0;
	va_start(argp, str);
	while (str[i] != '\0')
	{
		if (str[i] != '%')
			printed_bytes = ft_iputchar_fd(str[i], fd);
		else
		{
			i++;
			printed_bytes = ft_print_special_char(argp, str[i], fd);
		}
		if (printed_bytes < 0)
			return (printed_bytes);
		num_bytes = num_bytes + printed_bytes;
		i++;
	}
	va_end(argp);
	return (num_bytes);
}*/
