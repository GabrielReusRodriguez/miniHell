/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:14:49 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/10 18:49:47 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

int	ft_printf_fd_int(va_list argp, int fd)
{
	int		arg_value;
	int		bytes;
	char	*num;

	arg_value = va_arg(argp, int);
	num = ft_itoa(arg_value);
	if (num != NULL)
		return (-1);
	bytes = ft_iputstr_fd(num, fd);
	return (bytes);
}

int	ft_printf_int(va_list argp)
{
	return (ft_printf_fd_int(argp, STDOUT_FILENO));
}
