/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 20:04:11 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/11 01:46:14 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datatypes.h"
#include "environment.h"
#include "error_handler.h"
#include "tokens.h"
#include "ptr.h"
#include "expansor.h"

#include <stdio.h>

size_t	expansor_vars_find_end_var(t_string str, size_t init)
{
	size_t	j;

	j = 0;
	if (str[init + j] == '\0' || !(ft_isalpha(str[init + j]) || tokenizer_charinset(str[init + j], "_")))
		return (0);
	while (ft_isalnum(str[init + j]) || tokenizer_charinset(str[init + j], "_"))
		j++;
	return (j);
	

/*
	//if (ft_isdigit(str[init + j]) == 1)
	if (ft_isdigit(str[init + j]) == 1 || str[init + j] == '\"' || str[init + j] == '\'')
		return (j - 1);
//	while (str[init + j] != '\0' || str[init + j] != '\"')
	while (str[init + j] != '\0')
	{

//		if (str[init + j] == '\"' || str[init + j] == '\'')
//				//return (j - 1);
//				return (j);
//		if (ft_isalnum(str[init + j]) == 0)
//			break;

		
		if (ft_isalpha(str[init + j]) == 0)
			return (j - 1);
		j++;
	}
	return (j - 1);
*/
}

/*
size_t	expansor_vars_find_end_var(t_string str, size_t init)
{
	size_t	j;

	j = 1;
	//if (ft_isdigit(str[init + j]) == 1)
	if (ft_isdigit(str[init + j]) == 1 || str[init + j] == '\"' || str[init + j] == '\'')
		return (j - 1);
//	while (str[init + j] != '\0' || str[init + j] != '\"')
	while (str[init + j] != '\0')
	{

//		if (str[init + j] == '\"' || str[init + j] == '\'')
//				//return (j - 1);
//				return (j);
//		if (ft_isalnum(str[init + j]) == 0)
//			break;

		
		if (ft_isalpha(str[init + j]) == 0)
			return (j - 1);
		j++;
	}
	return (j - 1);
}
*/
/*
size_t	expansor_vars_find_end_var(t_string str, size_t init)
{
	size_t	j;

	j = 1;
	//if (ft_isdigit(str[init + j]) == 1)
	if (ft_isdigit(str[init + j]) == 1 || str[init + j] == '\"' || str[init + j] == '\'')
		return (j);
//	while (str[init + j] != '\0' || str[init + j] != '\"')
	while (str[init + j] != '\0')
	{		
		if (ft_isalpha(str[init + j]) == 0)
			return (j - 1);
		j++;
	}
	return (j);
}
*/

t_string	expansor_vars_get_var(t_string str, size_t init, size_t *end_var, t_environment *env)
{
	t_var		*var;
	t_string	var_key;
	t_string	var_value;
	size_t		size_var;
	
	size_var = expansor_vars_find_end_var(str, init);
	if (size_var == 0)
	{
		(*end_var) = init + size_var;
		/*
		if (str[init + size_var] == '\0')
		{
		//		printf(" j = 0\n");
			var_value = ft_strdup("$");
			if (var_value == NULL)
				error_system_crash("Error at memory malloc\n");	
		}
		printf("\t\tFINAL VALUE RETURNED EXCEPTION _%s_\n", var_value);
		*/
		var_value = ft_strdup("");
		if (var_value == NULL)
			error_system_crash("Error at memory malloc\n");	
		return (var_value);
	}
	*end_var = init + size_var;
	//var_key = ft_substr(str, init + 1, *end_var - init);
	var_key = ft_substr(str, init, *end_var - init);
//	printf("\tVAR buscada : _%s_\n", var_key);
	if (var_key == NULL)
		error_system_crash("Error at memory malloc\n");	
	var = env_get_var(*env, var_key);
	if (var != NULL)
		var_value = ft_strdup(var->value);
	else
		var_value = ft_strdup("");
	if (var_value == NULL)
		error_system_crash("Error at memory malloc\n");	
	free (var_key);
	return (var_value);
}

size_t	expansor_vars_count_vars(t_string str)
{
	size_t	num;
	size_t	i;
	bool	replace_mode;

	num = 0;
	i = 0;
	replace_mode = true;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			replace_mode = !replace_mode;
			i++;
			continue;
		}
		if(replace_mode == true && str[i] == '$')
			num++;
		i++;
	}
	return (num + 1);
}

t_string	*expansor_vars_create_chunks(t_string str)
{
	t_string	*chunks;
	size_t		num_chunks;
	size_t		i;

	num_chunks = expansor_vars_count_vars(str);
//	printf("Num chunks = %lu\n", num_chunks);
	chunks = (t_string *)malloc((num_chunks + 1)*sizeof(t_string));
	if (chunks == NULL)
		error_system_crash("Error at memory malloc\n");
	i = 0;
	while (i <= num_chunks)
	{
		chunks[i] = NULL;
		i++;
	}
	return (chunks);
}

t_string	expansor_vars_join_chunks(t_string *chunks)
{
	t_string	str_joined;
	t_string	aux;
	size_t		i;

	i = 0;
	str_joined = ft_strdup("");
	if (str_joined == NULL)
		error_system_crash("ERROR at memory malloc\n");
	while (chunks[i] != NULL)
	{
		aux = str_joined;
		printf("chunk: %s \n",chunks[i]);
		str_joined = ft_strjoin(str_joined, chunks[i]);
		if (str_joined == NULL)
			error_system_crash("ERROR at memory malloc\n");
		free (aux);
		i++;
	}
	return (str_joined);
}

/*
	Hacemos un array de chunks.
	Vamos iterando y nos guardamos en una variable (init) el ultimo punto del string del que hicimos 
		push al array de chunks.
		
	El algoritmo es :
		Si es un word de tipo SQUOTE => fuera
		Si encontramos un $ (si elinit NO es igual al i significa que hemos recorrido texto por lo 
			que nos toca hacer un nuevo chunk antes de substituir la variable)
		En caso que la palabta sea un $ y el siguiente token sea un espacio O sea el último token
			IMPRIMIMOS el $.
		Si no, es seguramente el caso de $"asdasda" por lo que NO imprimimos el $ y llamamos al expansor
			para encontrar el valor de la variable.
		Sólo nos queda que al salir del while, actualizar el array de chunks con lo que nos queda pendiente.
*/
/*
void	expansor_vars_replace_vars(t_token *token, t_token *next_t,t_environment *env)
{
	t_string	*chunks;
	size_t		i;
	size_t		j;
	size_t		init;

	if (token->type == TOKEN_TYPE_WORD_SQUOTE)
		return ;
	chunks = expansor_vars_create_chunks(token->value);
	i = 0;
	init = i;
	j = 0;
	while (token->value[i] != '\0')
	{
		if (token->value[i] == '$')
		{
			if (init < i)
			{
				chunks[j] = ft_substr(token->value, init, i - init);
				if (chunks[j] == NULL)
					error_system_crash("Error at memory malloc\n");
				j++;
			}
			if (token->value[i + 1] == '\0' && (next_t == NULL || next_t->type == TOKEN_TYPE_SPACE))
			{
				chunks[j++] = ft_strdup("$");
				if (chunks[j - 1] == NULL)
					error_system_crash("Error at memory malloc\n");
				init = i + 1;
				i = init;
				continue;
			}
			if (token->value[i + 1] == '?')
			{
				chunks[j++] = ft_strdup("-1");
				if (chunks[j - 1] == NULL)
					error_system_crash("Error at memory malloc\n");
				init = i + 2;
				i = init;
				continue;
			}
			chunks[j++] = expansor_vars_get_var(token->value, i + 1, &init, env);
			i = init;
		}
		else
			i++;
	}
	if (init < i)
	{
			chunks[j] = ft_substr(token->value, init, i - init);
			if (chunks[j] == NULL)
				error_system_crash("Error at memory malloc\n");
	}
	free (token->value);
	token->value = expansor_vars_join_chunks(chunks);
	ptr_freematrix(chunks);
}
*/

static t_string expansor_vars_join(t_string origin, t_string destiny)
{
	t_string	res;
	
	res = ft_strjoin(origin, destiny);
	free (origin);
	free (destiny);
	if (res == NULL)
		error_system_crash("Error at memory malloc\n");
	return (res);
}

static t_string	expansor_vars_join_acumulated(t_string acum, t_expansor limits)
{
	t_string	res;
	t_string	substring;

	substring = ft_substr(limits.str, limits.init, limits.i - limits.init);
	if (substring == NULL)
		error_system_crash("Error at memory malloc\n");
	res = expansor_vars_join(acum, substring);
	return (res);
}
/*
static t_string expansor_vars_dollar_found(t_string str, size_t *init, size_t *i,t_token *next_t)
{
	if (init < i)
	{
		expansor_vars_join_acumulated(t_string str, acum, *init, *i);
		substring = ft_substr(str, init, i - init);
		if (substring == NULL)
			error_system_crash("Error at memory malloc\n");
		expanded = expansor_vars_join(expanded, substring);
	}
	if (token->value[i + 1] == '\0' && (next_t == NULL || next_t->type == TOKEN_TYPE_SPACE))
	{
		substring = ft_strdup("$");
		if (substring == NULL)
			error_system_crash("Error at memory malloc\n");
		expanded = expansor_vars_join(expanded, substring);
		init = i + 1;
		i = init;
		continue;
	}
	if (token->value[i + 1] == '?')
	{
		substring = ft_strdup("-1");
		if (substring == NULL)
			error_system_crash("Error at memory malloc\n");
		expanded = expansor_vars_join(expanded, substring);
		init = i + 2;
		i = init;
		continue;
	}
	substring = expansor_vars_get_var(token->value, i + 1, &init, env);
	if (substring == NULL)
		error_system_crash("Error at memory malloc\n");
	expanded = expansor_vars_join(expanded, substring);
	i = init;
	return (expanded);
}
*/

static t_string	expansor_vars_replace_status(t_string acum, t_expansor *limits)
{
	t_string	substring;
	t_string	res;
	
	
	substring = ft_strdup("-1");
	if (substring == NULL)
		error_system_crash("Error at memory malloc\n");
	res = expansor_vars_join(acum, substring);
	limits->i = limits->i + 2;
	limits->init = limits->i;
	return (res);
}

static t_string	expansor_vars_add_dollar(t_string acum, t_expansor *limits)
{
	t_string	substring;
	t_string	res;
	
	substring = ft_strdup("$");
	if (substring == NULL)
		error_system_crash("Error at memory malloc\n");
	res = expansor_vars_join(acum, substring);
	limits->i++;
	limits->init = limits->i;
	return (res);
}


static t_string	expansor_vars_replace_vars_init(t_expansor	*limits, t_string str)
{
	t_string	expanded;

	expanded = ft_strdup("");
	if (expanded == NULL)
		error_system_crash("Error at memory malloc\n");
	limits->i = 0;
	limits->init = 0;
	limits->str = str;
	return (expanded);
}

/*
El caso  if (limits->str[limits->i + 1] == '\0' && (next_t == NULL || next_t->type == TOKEN_TYPE_SPACE))
es para que no pinte el dolar antes en $"PATH" ya que como un chunk seria $ y el siguiente
seria DQWORD, pintaria el dolar y luego la var.
*/
static t_string	expansor_vars_replace_loop(t_string expanded, t_expansor *limits, t_token *next_t, t_environment *env)
{
	t_string	substring;

	if (limits->str[limits->i] == '$')
	{
		if (limits->init < limits->i)
			expanded = expansor_vars_join_acumulated(expanded, *limits);
		if (limits->str[limits->i + 1] == '\0' && (next_t == NULL || next_t->type == TOKEN_TYPE_SPACE))
		{
			expanded = expansor_vars_add_dollar(expanded, limits);
			return (expanded);
		}
		if (limits->str[limits->i + 1] == '?')
		{
			expanded = expansor_vars_replace_status(expanded, limits);
			return (expanded);
		}
		substring = expansor_vars_get_var(limits->str, limits->i + 1, &limits->init, env);
		expanded = expansor_vars_join(expanded, substring);
		limits->i = limits->init;
	}
	else
		limits->i++;
	return (expanded);
}

void	expansor_vars_replace_vars(t_token *token, t_token *next_t,t_environment *env)
{
	t_string			expanded;
	t_expansor			expansor;

	if (token->type == TOKEN_TYPE_WORD_SQUOTE)
		return ;
	expanded = expansor_vars_replace_vars_init(&expansor, token->value);
	while (token->value[expansor.i] != '\0')
	{
		expanded = expansor_vars_replace_loop(expanded, &expansor, next_t, env);
	}
	if (expansor.init < expansor.i)
		expanded = expansor_vars_join_acumulated(expanded, expansor);
	free (token->value);
	token->value = expanded;
}

/*
void	expansor_vars_replace_vars(t_token *token, t_token *next_t,t_environment *env)
{
	t_string			substring;
	t_string			expanded;
	t_expansor_chunk	limits;

	if (token->type == TOKEN_TYPE_WORD_SQUOTE)
		return ;
	expanded = expansor_vars_replace_vars_init(&limits);
	while (token->value[limits.i] != '\0')
	{
		if (token->value[limits.i] == '$')
		{
			if (limits.init < limits.i)
				expanded = expansor_vars_join_acumulated(token->value, expanded, limits);
			if (token->value[limits.i + 1] == '\0' && (next_t == NULL || next_t->type == TOKEN_TYPE_SPACE))
			{
				expanded = expansor_vars_add_dollar(expanded, &limits);
				continue;
			}
			if (token->value[limits.i + 1] == '?')
			{
				expanded = expansor_vars_replace_status(expanded, &limits);
				continue;
			}
			substring = expansor_vars_get_var(token->value, limits.i + 1, &limits.init, env);
			expanded = expansor_vars_join(expanded, substring);
			limits.i = limits.init;
		}
		else
			limits.i++;
	}
	if (limits.init < limits.i)
		expanded = expansor_vars_join_acumulated(token->value, expanded, limits);
	free (token->value);
	token->value = expanded;
}
*/


/*
void	expansor_vars_replace_vars(t_token *token, t_token *next_t,t_environment *env)
{
	t_string	aux;
	t_string	substring;
	size_t		i;
	size_t		init;
	t_string	expanded;

	if (token->type == TOKEN_TYPE_WORD_SQUOTE)
		return ;
	//chunks = expansor_vars_create_chunks(token->value);
	expanded = ft_strdup("");
	if (expanded == NULL)
		error_system_crash("Error at memory malloc\n");
	i = 0;
	init = i;
	while (token->value[i] != '\0')
	{
		if (token->value[i] == '$')
		{
			printf("DOLAR ENCONTRADO!!\n");
			if (init < i)
			{
				substring = ft_substr(token->value, init, i - init);
				if (substring == NULL)
					error_system_crash("Error at memory malloc\n");
				aux = expanded;
				expanded = ft_strjoin(expanded, substring);
				free  (aux);
				free (substring);
				if (expanded == NULL)
					error_system_crash("Error at memory malloc\n");
			}
			if (next_t != NULL)
				printf("Tipo de next es: %d \n", next_t->type);
			if (
					(token->value[i + 1] == '\0' && (next_t == NULL || next_t->type == TOKEN_TYPE_SPACE))
				)
			{
				substring = ft_strdup("$");
				if (substring == NULL)
					error_system_crash("Error at memory malloc\n");
				aux = expanded;
				expanded = ft_strjoin(expanded, substring);
				free  (aux);
				free (substring);
				if (expanded == NULL)
					error_system_crash("Error at memory malloc\n");
				init = i + 1;
				i = init;
				continue;
			}
			if (token->value[i + 1] == '?')
			{
				substring = ft_strdup("-1");
				if (substring == NULL)
					error_system_crash("Error at memory malloc\n");
				aux = expanded;
				expanded = ft_strjoin(expanded, substring);
				free  (aux);
				free (substring);
				if (expanded == NULL)
					error_system_crash("Error at memory malloc\n");
				init = i + 2;
				i = init;
				continue;
			}
			substring = expansor_vars_get_var(token->value, i + 1, &init, env);
			if (substring == NULL)
				error_system_crash("Error at memory malloc\n");
			aux = expanded;
			expanded = ft_strjoin(expanded, substring);
			free  (aux);
			free (substring);
			if (expanded == NULL)
				error_system_crash("Error at memory malloc\n");
			i = init;
		}
		else
			i++;
	}
	if (init < i)
	{
			substring = ft_substr(token->value, init, i - init);
			if (substring == NULL)
				error_system_crash("Error at memory malloc\n");
			aux = expanded;
			expanded = ft_strjoin(expanded, substring);
			free  (aux);
			free (substring);
			if (expanded == NULL)
				error_system_crash("Error at memory malloc\n");
	}
	free (token->value);
	token->value = expanded;
}
*/

/*
void	expansor_vars_replace_vars(t_token *token, t_environment *env)
{
	t_string	*chunks;
	size_t		i;
	size_t		j;
	size_t		init;

	if (token->type == TOKEN_TYPE_WORD_SQUOTE)
		return ;
	chunks = expansor_vars_create_chunks(token->value);
	i = 0;
	init = i;
	j = 0;
	printf("TOKEN: _%s_\n",token->value);
	while (token->value[i] != '\0')
	{
		printf("CHECK %c init %lu i %lu\n", token->value[i], init, i);
		if (token->value[i] == '$')
		{
			if (init < i)
			{
				printf("actualizacion %c init %lu i %lu\n", token->value[i], init, i);
				chunks[j] = ft_substr(token->value, init, i - init);
				if (chunks[j] == NULL)
					error_system_crash("Error at memory malloc\n");
				j++;
			}
			chunks[j++] = expansor_vars_get_var(token->value, i + 1, &init, env);
			//if (token->value[init] != '\0')
				i = init;
			//printf("final loop %c init %lu i %lu\n", token->value[i], init, i);
			printf("final loop init %lu i %lu\n", init, i);
		}
		else
			i++;
	}
	if (init < i)
	{
			chunks[j] = ft_substr(token->value, init, i - init);
//			printf("CHUNKS : i %lu init %lu %s \n", i, init, chunks[j]);
			if (chunks[j] == NULL)
				error_system_crash("Error at memory malloc\n");
	}
	free (token->value);
	token->value = expansor_vars_join_chunks(chunks);
	ptr_freematrix(chunks);
}
*/
/*
bool	expansor_var_is_valid(t_token *token)
{
	t_string	value;
	size_t		i;

	value = token->value;
	i = 0;
	while (value[i] != '\0')
	{
		
	}
}*/