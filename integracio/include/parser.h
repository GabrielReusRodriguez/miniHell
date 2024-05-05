/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:20:46 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/05 02:18:45 by gabriel          ###   ########.fr       */
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
void	*parser_get_cmdset(t_token_set *token_set, t_cmd_set	*cmd_set);
size_t	parser_count_cmds(t_token_set token_set);
void	*parser_get_next_cmd(t_token_set *token_set, t_cmd *cmd);
void	*parser_create_cmd(t_list *first_token, t_list *last_token, t_cmd *cmd);

/*
	parser_utils.c
*/
bool	parser_iscmdseparator(t_token token);

/*
	parser_getters_redirect.c
*/
void	*parser_parse_redir(t_list **list, t_list *end, t_cmd *cmd);
//void	*parser_parse_redir_v2(t_list **list, t_list *end, t_cmd *cmd);

/*
	parser_getters_cmd.c
*/
void	*parser_parse_word(t_token *token, t_cmd *cmd);

#endif
