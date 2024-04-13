/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:57:57 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/10 19:13:58 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>

int		ft_printf(char const *str, ...);
int		ft_printf_char(va_list argp);
int		ft_printf_str(va_list argp);
int		ft_printf_ptr(va_list argp);
int		ft_printf_dec(va_list argp);
int		ft_printf_int(va_list argp);
int		ft_printf_usgn(va_list argp);
int		ft_printf_low_hex(va_list argp);
int		ft_printf_up_hex(va_list argp);
char	*ft_printf_htoa(unsigned long u_number, unsigned int up_case);
int		ft_printf_percent(void);

int		ft_printf_fd(int fd, char const *str, ...);
int		ft_printf_fd_char(va_list argp, int fd);
int		ft_printf_fd_str(va_list argp, int fd);
int		ft_printf_fd_ptr(va_list argp, int fd);
int		ft_printf_fd_dec(va_list argp, int fd);
int		ft_printf_fd_int(va_list argp, int fd);
int		ft_printf_fd_usgn(va_list argp, int fd);
int		ft_printf_fd_low_hex(va_list argp, int fd);
int		ft_printf_fd_up_hex(va_list argp, int fd);
int		ft_printf_fd_htoa(unsigned long u_number, unsigned int up_case);
int		ft_printf_fd_percent(int fd);

#endif