/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:20:46 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/24 23:00:55 by gabriel          ###   ########.fr       */
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

# define PARSER_SEPARATORS "|&;"

size_t  parser_count_cmds(t_token_set token_set);


#endif
