/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:59:13 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/15 22:58:54 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTIN_H
# define FT_BUILTIN_H

#include "ft_minishell.h"
#include "ft_datatypes.h"

# define BUILTIN_EXIT	"exit"
# define BUILTIN_ECHO	"echo"
# define BUILTIN_CD		"cd"
# define BUILTIN_PWD	"pwd"
# define BUILTIN_EXPORT	"export"
# define BUILTIN_UNSET	"unset"
# define BUILTIN_ENV	"env"

void    ft_builtin_exit(t_minishell *shell);
/*
	A partir de aqui los builtin están en todo por lo que los parmámetros
		casi seguro que cambiaran.
*/
void	ft_builtin_echo(void);
void	ft_builtin_cd(void);
void	ft_builtin_pwd(void);
void	ft_builtin_export(void);
void	ft_builtin_unset(void);
void	ft_builtin_env(void);
t_bool	ft_builin_isbuiltin(t_string cmd);

#endif