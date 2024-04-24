/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:27:53 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/24 21:47:16 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CMD_H
# define FT_CMD_H

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
	t_list		*first_token;
	t_list		*last_token;
	t_token		*exec;
	t_list		*args;
	t_token		*red_in;
	t_token		*red_in_origin;
	t_token		*red_out;
	t_token		*red_out_dest;
	int			pipe[2];
	int			status;
}	t_cmd;

t_cmd	ft_cmd_new(void);
void	ft_cmd_destroy(t_cmd *cmd);
bool	ft_cmd_isvalid(t_cmd cmd);
bool	ft_cmd_isbuiltin(t_cmd cmd);

#endif
