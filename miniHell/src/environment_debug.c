/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_debug.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:42:37 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/12 23:24:07 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "environment.h"
#include "var.h"
#include "debug.h"

void	env_debug(t_environment env)
{
	t_list	*node;
	t_var	*var;

	if (DEBUG_MODE)
	{
		node = env.vars;
		printf("DEBUG ENV**************************************\n");
		while (node != NULL)
		{
			var = (t_var *)node->content;
			printf("\t %s = %s\n", var->key, var->value);
			node = node->next;
		}
		printf("DEBUG ENV END**************************************\n");
	}
}
