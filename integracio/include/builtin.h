/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 02:19:14 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/02 23:57:56 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "cmd.h"

# define BUILTIN_EXIT	"exit"
# define BUILTIN_ECHO	"echo"
# define BUILTIN_CD		"cd"
# define BUILTIN_PWD	"pwd"
# define BUILTIN_EXPORT	"export"
# define BUILTIN_UNSET	"unset"
# define BUILTIN_ENV	"env"

void    builtin_cd(t_minishell *shell, t_cmd cmd);
void    builtin_echo(t_minishell *shell, t_cmd cmd);
void    builtin_pwd(t_minishell *shell, t_cmd cmd);
void	builtin_exit(t_minishell *shell);
void    builtin_env(t_minishell *shell);
void	builtin_export(t_minishell *shell, t_cmd cmd);
void	builtin_unset(t_minishell *shell, t_cmd cmd);
bool    builtin_isbuiltin(t_cmd cmd);
void    builtin_exec(t_minishell *shell, t_cmd cmd);


#endif
