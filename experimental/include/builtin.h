/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 02:19:14 by abluis-m          #+#    #+#             */
/*   Updated: 2024/06/02 21:11:08 by greus-ro         ###   ########.fr       */
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

int		builtin_exit(t_minishell *shell, t_cmd cmd);
int		builtin_echo(t_cmd cmd);
int		builtin_run(t_minishell *shell, t_cmd cmd);
int		builtin_cd(t_minishell *shell, t_cmd cmd);
int		builtin_pwd(t_minishell *shell, t_cmd cmd);
int		builtin_env(t_minishell *shell);
int		builtin_export(t_minishell *shell, t_cmd cmd);
int		builtin_unset(t_minishell *shell, t_cmd cmd);

/*
	builtin_export.c
*/
int		builtin_export_destroy(t_var *var, t_minishell *shell);

/*
	builtin_export2.c
*/
int		builtin_export_wargs(t_minishell *shell, t_list *args);
void	builtin_export_minishell_refresh_vars(t_minishell *shell, \
					t_string param);

#endif
