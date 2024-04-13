/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:19:39 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/10 19:17:29 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "ft_printf.h"

static char	*ft_add_ptr_header(char *str_ptr)
{
	char				*aux;

	aux = ft_strjoin("0x", str_ptr);
	free (str_ptr);
	return (aux);
}

int	ft_printf_fd_ptr(va_list argp, int fd)
{
	void	*ptr;
	char	*str_ptr;	
	size_t	size;
	int		num_bytes;

	ptr = va_arg(argp, void *);
	if (ptr == NULL)
	{
		size = 1 + 1;
		str_ptr = ft_ptr_new_char_buffer(size);
		if (str_ptr == NULL)
			return (-1);
		ft_strlcpy(str_ptr, "0", size);
	}
	else
		str_ptr = ft_dtoh((unsigned long)ptr, 0);
	if (str_ptr == NULL)
		return (-1);
	str_ptr = ft_add_ptr_header(str_ptr);
	num_bytes = ft_iputstr_fd(str_ptr, fd);
	free(str_ptr);
	return (num_bytes);
}

int	ft_printf_ptr(va_list argp)
{
	return (ft_printf_fd_ptr(argp, STDOUT_FILENO));
}
