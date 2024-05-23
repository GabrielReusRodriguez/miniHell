/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 02:19:14 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/04 15:33:44 by abluis-m         ###   ########.fr       */
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

int		builtin_exit(t_minishell *shell, t_cmd cmd, bool parent);
int		builtin_echo(t_cmd cmd);
int		builtin_run(t_minishell *shell, t_cmd cmd, bool parent);
int		builtin_cd(t_minishell *shell, t_cmd cmd);
int		builtin_pwd(t_minishell *shell, t_cmd cmd);
int		builtin_env(t_minishell *shell);
int		builtin_export(t_minishell *shell, t_cmd cmd);
int		builtin_unset(t_minishell *shell, t_cmd cmd);

#endif
