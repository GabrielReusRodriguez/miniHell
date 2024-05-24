/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 19:01:08 by abluis-m          #+#    #+#             */
/*   Updated: 2023/10/07 19:06:21 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	len;

	len = (n == 0);
	while (n)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	else
		return (n);
}

void	ft_revstr(char *str, int length)
{
	int		start;
	int		end;
	char	aux;

	start = 0;
	end = length -1;
	while (start < end)
	{
		aux = str[start];
		str[start] = str[end];
		str[end] = aux;
		end--;
		start++;
	}
}

char	*ft_itoa(int n)
{
	char	*number;
	int		len;
	int		isnegative;

	isnegative = (n < 0);
	len = ft_intlen(n);
	number = (char *)ft_calloc((len + isnegative + 1), sizeof(char));
	if (!number)
		return (NULL);
	len = 0;
	number[len++] = 0;
	if (n == 0)
		number[len++] = '0';
	while (n != 0)
	{
		number[len++] = '0' + ft_abs(n % 10);
		n = n / 10;
	}
	if (isnegative)
		number[len++] = '-';
	ft_revstr(number, len);
	return (number);
}
