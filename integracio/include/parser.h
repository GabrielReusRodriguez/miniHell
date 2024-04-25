/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:20:46 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/25 23:25:13 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//TODO: WORK IN PROGRESS.....
/*
Clase a medio hacer, se necesita el include para el tokenizer...
*/
# include "datatypes.h"
# include "tokens.h"
# include "cmd.h"

# define PARSER_CMD_SEPARATORS "|&;"

/*
	parser.c
*/
void	*parser_get_cmds(t_token_set *token_set, t_cmd_set	*cmd_set);
size_t  parser_count_cmds(t_token_set token_set);
void	*parser_get_next_cmd(t_token_set *token_set, t_cmd *cmd);
bool	parser_iscmdseparator(t_token token);
void	*parse_create_cmd(t_list *first_token, t_list *last_token, t_cmd *cmd);

/*
	parser_utils.c
*/
bool	parser_iscmdseparator(t_token token);

/*
	parser_getters_redirect.c
*/
t_token *parser_get_redir_input(t_list **token_list_node, t_list *end_cmd);
t_token	*parser_get_redir_input_origin(t_list **token_list_node, \
				t_list *end_cmd);
t_token	*parser_get_redir_output(t_list **token_list_node, t_list *end_cmd);
t_token	*parser_get_redir_output_dest(t_list **token_list_node, \
            t_list *end_cmd);


/*
	parser_getters_cmd.c
*/
t_token	*parser_get_exec(t_list **token_list_node, t_list *end_cmd);
t_list	*parser_get_args(t_list **token_list_node, t_list *end_cmd);



#endif
