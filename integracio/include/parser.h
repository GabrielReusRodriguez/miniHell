/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:20:46 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/23 17:22:10 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

/*
Clase a medio hacer, se necesita el include para el tokenizer...
*/
# include "datatypes.h"
# include "tokens.h"
//# include "ft_cmd.h"

# define PARSER_SEPARATORS  " \t\v\n"

/*
bool		ft_parser_validate_tokenset(t_token_set token_set);
t_cmd		ft_parser_get_next_comand(t_token_set *token_set);
t_string	ft_parser_sublist_2_str(t_token *first, t_token *last);
bool		ft_parser_has_morecmds(t_token_set token_set);
t_token		*ft_parser_get_redir_input(t_list **token_list_node, t_list *end_cmd);
t_token		*ft_parser_get_redir_input_origin(t_list **token_list_node, t_list *end_cmd);
t_token		*ft_parser_get_exec(t_list **token_list_node, t_list *end_cmd);
t_list		*ft_parser_get_args(t_list **token_list_node, t_list *end_cmd);
t_token		*ft_parser_get_redir_output(t_list **token_list_node, t_list *end_cmd);
t_token		*ft_parser_get_redir_output_dest(t_list **token_list_node, t_list *end_cmd);
t_token		*ft_parser_get_stopper(t_list **token_list_node, t_list *end_cmd);
t_cmd		ft_parser_get_next_comand(t_token_set *token_set);
void		*ft_parser_parse_command(t_cmd *cmd);
bool		ft_parser_isstopper(t_token token);
*/

#endif
