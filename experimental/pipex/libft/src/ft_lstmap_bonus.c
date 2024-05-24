/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:00:56 by abluis-m          #+#    #+#             */
/*   Updated: 2024/01/04 11:33:32 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*chain;
	t_list	*link;
	void	*current;

	if (!f || !del)
		return (NULL);
	chain = NULL;
	while (lst)
	{
		current = f(lst->content);
		link = ft_lstnew(current);
		if (!link)
		{
			del(current);
			ft_lstclear(&chain, del);
			return (NULL);
		}
		ft_lstadd_back(&chain, link);
		lst = lst->next;
	}
	ft_lstclear(&lst, del);
	return (chain);
}
