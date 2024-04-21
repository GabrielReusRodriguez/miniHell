/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 20:26:47 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/21 22:41:39 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

# include "ft_datatypes.h"
# include "ft_cmd.h"

# define PARSER_SEPARATORS  " \t\v\n"

t_bool		ft_parser_validate_tokenset(t_token_set token_set);
t_cmd		ft_parser_get_next_comand(t_token_set *token_set);
t_string	ft_parser_sublist_2_str(t_token *first, t_token *last);
t_bool		ft_parser_has_morecmds(t_token_set token_set);
t_token		*ft_parser_get_redir_input(t_list **token_list_node, t_list *end_cmd);
t_token		*ft_parser_get_redir_input_origin(t_list **token_list_node, t_list *end_cmd);
t_token		*ft_parser_get_exec(t_list **token_list_node, t_list *end_cmd);
t_list		*ft_parser_get_args(t_list **token_list_node, t_list *end_cmd);
t_token		*ft_parser_get_redir_output(t_list **token_list_node, t_list *end_cmd);
t_token		*ft_parser_get_redir_output_dest(t_list **token_list_node, t_list *end_cmd);
t_token		*ft_parser_get_stopper(t_list **token_list_node, t_list *end_cmd);
t_cmd		ft_parser_get_next_comand(t_token_set *token_set);
void		*ft_parser_parse_command(t_cmd *cmd);
t_bool		ft_parser_isstopper(t_token token);

#endif