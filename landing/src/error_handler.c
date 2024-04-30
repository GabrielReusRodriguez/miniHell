/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:15:29 by gabriel           #+#    #+#             */
/*   Updated: 2024/04/30 20:15:42 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "datatypes.h"
#include "libft.h"

void	error_print(t_cstring msg)
{
	size_t	len;

	len = ft_strlen(msg);
	write(STDERR_FILENO, msg, len);
}
