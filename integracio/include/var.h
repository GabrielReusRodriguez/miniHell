/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:32:51 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/01 19:56:49 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_H
# define VAR_H

# include "datatypes.h"

typedef struct s_var
{
	t_string	key;
	t_string	value;
}	t_var;

/*
	var.c
*/
t_var		var_new(void);
t_var		*var_init(t_string str, t_var *var);
t_var		*var_clone(t_var var);
t_string	var_2_string(t_var var);
void		var_destroy(t_var	*var);
t_var		var_getenvvar(t_string var_name);

#endif