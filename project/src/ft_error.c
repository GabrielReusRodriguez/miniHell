/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:43:05 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/10 20:54:29 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
//#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "ft_datatypes.h"
//#include "libft.h"
#include "ft_printf.h"

void ft_error_print_msg(t_string msg)
{
	ft_printf_fd(STDERR_FILENO, "%s", msg);
}

void ft_error_print_errno(t_string msg)
{
	perror(msg);
}

void ft_error_print_errnum(t_string msg, int errnum)
{
	t_string	str_error;

	str_error = strerror(errnum);
	ft_printf_fd(STDERR_FILENO, "%s", msg);
	ft_printf_fd(STDERR_FILENO, ": ");
	ft_printf_fd(STDERR_FILENO, "%s", str_error);
}