/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:17:13 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/29 22:18:45 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PERM_H
# define PERM_H

# define PERM_OK 0
# define PERM_NO_FILE 400
# define PERM_NO_READ 404
# define PERM_NO_WRITE 402
# define PERM_NO_EXEC 126
# define PERM_NO_COMMAND 127
# define PERM_IS_DIR    126

# include "datatypes.h"
# include "cmd.h"

/*
    permission_exec.c
*/
bool permission_exec_check(t_cmd *cmd);
bool permission_exec_check_with_path(t_cmd *cmd, t_string *paths);


#endif
