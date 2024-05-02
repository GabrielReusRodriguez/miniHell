/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:27:53 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/02 23:51:58 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "datatypes.h"
# include "libft.h"
# include "tokens.h"

//TODO: WORK IN PROGRESS

typedef enum e_cmd_type
{
	TYPE_REDIR_INPUT,
	TYPE_REDIR_OUTPUT,
	TYPE_PIPE,
	TYPE_AND,
	TYPE_OR
}	t_cmd_type;

typedef struct s_cmd
{
	t_token		*exec;
	t_list		*args;
	t_token		*red_in;
	t_token		*red_in_origin;
	t_token		*red_out;
	t_token		*red_out_dest;
	int			pipe[2];
	int			status;
}	t_cmd;

typedef struct s_cmd_set
{
	size_t	num_cmds;
	t_cmd	*cmds;
}	t_cmd_set;

/*
    cmd.c
*/
t_cmd		cmd_new(void);
void		cmd_destroy(t_cmd *cmd);
bool		cmd_isvalid(t_cmd cmd);
//bool		cmd_isbuiltin(t_cmd cmd);
void		cmd_destroy_set(t_cmd_set *cmd_set);
t_cmd_set	cmd_create_set(t_token_set token_set);

/*
    cmd_validator.c
*/
bool		cmd_validate_set(t_cmd_set cmd_set);

/*
    cmd_debug.c
*/
void		cmd_debug(t_cmd cmd);
#endif
