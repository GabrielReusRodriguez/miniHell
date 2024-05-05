/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:49:52 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/05 01:33:12 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

t_redirect	*redirect_new(void)
{
	t_redirect *redir;

	redir = (t_redirect *)malloc(sizeof(t_redirect));
	if (redir == NULL)
		return (NULL);
	redir->target = NULL;
	redir->type = NULL;
	return (redir);
}

/*
	We do not free any memory because they are pointers to token so they
	will be free when we "destroy" the tokens.
*/
void		redirect_freenode(void *arg)
{
	free(arg);
}