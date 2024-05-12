/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:15:29 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/12 23:23:40 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "datatypes.h"
#include "libft.h"

void	*error_print(t_cstring msg)
{
	size_t	len;

	len = ft_strlen(msg);
	write(STDERR_FILENO, msg, len);
	return (NULL);
}

void	error_system_crash(t_cstring msg)
{
	error_print(msg);
	exit(EXIT_FAILURE);
}
