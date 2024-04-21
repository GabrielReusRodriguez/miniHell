/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:27:53 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/21 22:39:52 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CMD_H
# define FT_CMD_H

# include "ft_datatypes.h"
# include "libft.h"
# include "ft_tokens.h"

typedef	enum e_cmd_type
{
	TYPE_REDIR_INPUT,
	TYPE_REDIR_OUTPUT,
	TYPE_PIPE,
	TYPE_AND,
	TYPE_OR
}	t_cmd_type;

typedef struct s_cmd
{
    t_list      *first_token;
    t_list      *last_token;
	//t_string	cmd;
    t_token     *exec;
    t_list      *args;
    t_token     *red_in;
    t_token     *red_in_origin;
    t_token     *red_out;
    t_token     *red_out_dest;   
    int         pipe[2];
    //pid_t       pid;
    int         status;
	
}	t_cmd;

t_cmd   ft_cmd_new(void);
void    ft_cmd_destroy(t_cmd *cmd);
t_bool  ft_cmd_isvalid(t_cmd cmd);
t_bool  ft_cmd_isbuiltin(t_cmd cmd);
/*
t_cmd	ft_cmd_get_next_comand(t_token_set *token_set);
void    *ft_cmd_get_exec(t_cmd *cmd);
void    *ft_cmd_get_redir_in(t_cmd *cmd);
//t_token *ft_cmd_get_redir_in_orig(t_cmd cmd);
void    *ft_cmd_get_redir_out(t_cmd *cmd);
//t_token *ft_cmd_get_redir_out_dest(t_cmd cmd);
t_token *ft_cmd_get_stopper(t_cmd cmd);
void	*ft_cmd_parse_command(t_cmd *cmd);
*/

#endif