/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:19:03 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/01 19:24:17 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*list_getlast(t_list	*list)
{
	t_list	*node;

	node = list;
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);	
}
