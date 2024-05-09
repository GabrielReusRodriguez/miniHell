/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 00:00:25 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/06 00:40:31 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "parser.h"
#include "error_handler.h"

/* Obtenemos el tamaño de la word pero pillando SOLO los caracteres validos
	para la word.
*/
/*
static size_t	tokenizer_get_word_size(t_string str)
{
	size_t	i;
	size_t	size;
	size_t	num_open_dquotes;

	num_open_dquotes = 0;
	i = 0;
	size = 0;
	while (str[i] != '\0' && (num_open_dquotes % 2 > 0 || (tokenizer_charinset(str[i], TOKENS_SEPARATORS) \
			== false && tokenizer_charinset(str[i], PARSER_CMD_SEPARATORS) == false)))
	{
		//if (tokenizer_charinset(str[i], "\"\'()") == false)
		if (tokenizer_charinset(str[i], "\"()") == false)
			size++;
		if (tokenizer_charinset(str[i], "\"") == true)
			num_open_dquotes++;
		i++;
	}
	return (size);

}
*/
/*
	Aqui obtenemos el valor del word, OJO!! que tenemos que 
	chequear si acaba en ) ya que el tokenizer de por si no 
	lo pilla

	Para eso tenemos que asegurarnos que ha acabado en \0 el str
	y luego mirar la anterior letra.
*/
/*
static t_string	tokenizer_get_word_value(t_string str, size_t *final_pos)
{
	size_t		i;
	size_t		j;
	size_t		num_chars;
	t_string	token_value;

	num_chars = tokenizer_get_word_size(str);
	token_value = (t_string)malloc(num_chars + 1);
	if (token_value == NULL)
		return (NULL);
	token_value[num_chars] = '\0';
	i = 0;
	j = 0;
	while (str[i] != '\0' && tokenizer_charinset(str[i], TOKENS_SEPARATORS) \
			== false && tokenizer_charinset(str[i], PARSER_CMD_SEPARATORS) == false)
	{
		if (tokenizer_charinset(str[i], "\"\'()") == false)
	//	if (tokenizer_charinset(str[i], "\'()") == false)
			token_value[j++] = str[i];
		i++;
	}
	*final_pos = *final_pos + i;
	if (str[i] == '\0' && tokenizer_charinset(str[i - 1], "()") == true)
		*final_pos = *final_pos - 1;
	return (token_value);
}D
*/
/*
static t_string	tokenizer_get_word_value(t_string str, size_t *final_pos)
{
	size_t		i;
	size_t		j;
	size_t		num_chars;
	t_string	token_value;
	size_t		num_open_dquotes;

	num_open_dquotes = 0;
	num_chars = tokenizer_get_word_size(str);
	token_value = (t_string)malloc(num_chars + 1);
	if (token_value == NULL)
		return (NULL);
	token_value[num_chars] = '\0';
	i = 0;
	j = 0;
//	while (str[i] != '\0' && tokenizer_charinset(str[i], TOKENS_SEPARATORS) 
//			== false && tokenizer_charinset(str[i], PARSER_CMD_SEPARATORS) == false)
	while (str[i] != '\0' && (num_open_dquotes % 2 > 0 || (tokenizer_charinset(str[i], TOKENS_SEPARATORS) \
			== false && tokenizer_charinset(str[i], PARSER_CMD_SEPARATORS) == false)))
	{
//	//	if (tokenizer_charinset(str[i], "\"\'()") == false)
		if (tokenizer_charinset(str[i], "\"()") == false)
			token_value[j++] = str[i];
		if (tokenizer_charinset(str[i], "\"") == true)
			num_open_dquotes++;
		i++;
	}
	*final_pos = *final_pos + i;
	if (str[i] == '\0' && tokenizer_charinset(str[i - 1], "()") == true)
		*final_pos = *final_pos - 1;
	return (token_value);
}
*/
#include <stdio.h>


static size_t	tokenizer_get_size_quoted(t_string str, size_t *i)
{
	char	quote;
	size_t	size;

	size = 1;
	quote = str[*i];
	(*i)++;
	while (str[*i] != '\0' && str[*i] != quote)
	{
		size++;
		(*i)++;
	}
	if (str[*i] != '\0')
	{
		size++;
		(*i)++;
	}
	return (size);
}

static size_t	tokenizer_get_word_size(t_string str)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while(str[i] != '\0' && (tokenizer_charinset(str[i], TOKENS_SEPARATORS) \
			== false && tokenizer_charinset(str[i], PARSER_CMD_SEPARATORS) == false))
	{
		if (str[i] == '\"' || str[i] == '\'')
			size+=tokenizer_get_size_quoted(str, &i);
		else
		{
			if (tokenizer_charinset(str[i], "()") ==false)
				size++;
			i++;
		}
	}
	printf("SIZE WORD %lu\n",size);
	return (size);
}


static t_string	tokenizer_get_word_value(t_string str, size_t *final_pos)
{
	size_t		i;
	size_t		j;
	size_t		num_chars;
	t_string	token_value;
	char		quote;

	num_chars = tokenizer_get_word_size(str);
	token_value = (t_string)malloc(num_chars + 1);
	if (token_value == NULL)
		error_system_crash("Error at malloc\n");
	token_value[num_chars] = '\0';
	i = 0;
	j = 0;
	while(str[i] != '\0' && (tokenizer_charinset(str[i], TOKENS_SEPARATORS) \
			== false && tokenizer_charinset(str[i], PARSER_CMD_SEPARATORS) == false))
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			printf("\tquotes\n");
			quote = str[i++];
			token_value[j++] = quote;
			while (str[i] != '\0' && str[i] != quote)
				token_value[j++] = str[i++];
			if (str[i] != '\0')
				token_value[j++] = str[i++];
			continue ;
		}
		else
		{
			if (tokenizer_charinset(str[i], "()") ==false)
				token_value[j++] = str[i];
		}
		i++;
	}
	*final_pos = *final_pos + i;
	return (token_value);
/*
//	while (str[i] != '\0' && tokenizer_charinset(str[i], TOKENS_SEPARATORS) 
//			== false && tokenizer_charinset(str[i], PARSER_CMD_SEPARATORS) == false)
	while (str[i] != '\0' && (num_open_dquotes % 2 > 0 || (tokenizer_charinset(str[i], TOKENS_SEPARATORS) \
			== false && tokenizer_charinset(str[i], PARSER_CMD_SEPARATORS) == false)))
	{
//	//	if (tokenizer_charinset(str[i], "\"\'()") == false)
		if (tokenizer_charinset(str[i], "\"()") == false)
			token_value[j++] = str[i];
		if (tokenizer_charinset(str[i], "\"") == true)
			num_open_dquotes++;
		i++;
	}
	*final_pos = *final_pos + i;
	if (str[i] == '\0' && tokenizer_charinset(str[i - 1], "()") == true)
		*final_pos = *final_pos - 1;
	return (token_value);

*/
}

/*
static t_string	tokenizer_get_word_value(t_string str, size_t *final_pos)
{
	size_t		i;
	size_t		j;
	size_t		num_chars;
	t_string	token_value;
	size_t		num_open_dquotes;

	num_open_dquotes = 0;
	num_chars = tokenizer_get_word_size(str);
	token_value = (t_string)malloc(num_chars + 1);
	if (token_value == NULL)
		error_system_crash("Error at malloc\n");
	token_value[num_chars] = '\0';
	i = 0;
	j = 0;
//	while (str[i] != '\0' && tokenizer_charinset(str[i], TOKENS_SEPARATORS) 
//			== false && tokenizer_charinset(str[i], PARSER_CMD_SEPARATORS) == false)
	while (str[i] != '\0' && (num_open_dquotes % 2 > 0 || (tokenizer_charinset(str[i], TOKENS_SEPARATORS) \
			== false && tokenizer_charinset(str[i], PARSER_CMD_SEPARATORS) == false)))
	{
//	//	if (tokenizer_charinset(str[i], "\"\'()") == false)
		if (tokenizer_charinset(str[i], "\"()") == false)
			token_value[j++] = str[i];
		if (tokenizer_charinset(str[i], "\"") == true)
			num_open_dquotes++;
		i++;
	}
	*final_pos = *final_pos + i;
	if (str[i] == '\0' && tokenizer_charinset(str[i - 1], "()") == true)
		*final_pos = *final_pos - 1;
	return (token_value);
}
*/

t_list	*tokenizer_new_word(t_string str, size_t *final_pos)
{
	t_list		*token_node;
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_WORD;
	token->value = tokenizer_get_word_value(str, final_pos);
	if(token->value == NULL)
	{
		free(token);
		return (NULL);
	}
	token_node = ft_lstnew(token);
	if (token_node == NULL)
	{
		token_free(token);
		return (NULL);
	}
	return (token_node);
}

/*
t_list	*tokenizer_new_word(t_string str, size_t *final_pos)
{
	t_list		*token_node;
	t_token		*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = TOKEN_TYPE_WORD;
	token->value = tokenizer_get_word_value(str, final_pos);
	if(token->value == NULL)
	{
		free(token);
		return (NULL);
	}
	token_node = ft_lstnew(token);
	if (token_node == NULL)
	{
		token_free(token);
		return (NULL);
	}
	return (token_node);
}
*/

/*
t_list	*tokenizer_new_word(t_string str, size_t *final_pos)
{
	t_token		*token;
	size_t		i;
	size_t		word_init;
	t_list		*token_node;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	i = 0;
	word_init = i;
	while (str[i] != '\0' && tokenizer_charinset(str[i], TOKENS_SEPARATORS) \
				== false && tokenizer_charinset(str[i], PARSER_CMD_SEPARATORS) \
				== false && tokenizer_charinset(str[i], "\"\')") \
				== false)
		i++;
	token->type = TOKEN_TYPE_WORD;
	token->value = ft_substr(str, word_init, i - word_init);
	if (token->value == NULL)
		return (token_free(token));
	*final_pos = *final_pos + i;
	token_node = ft_lstnew(token);
	if (token_node == NULL)
		return (token_free(token));
	return (token_node);
}
*/