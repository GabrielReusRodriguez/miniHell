/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:49:52 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/31 00:16:53 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "redirect.h"
#include "ptr.h"

t_redirect	*redirect_new(void)
{
	t_redirect	*redir;

	redir = (t_redirect *)safe_malloc(sizeof(t_redirect));
	redir->target = NULL;
	redir->type = NULL;
	return (redir);
}

/*
	We do not free any memory because they are pointers to token so they
	will be free when we "destroy" the tokens.
*/
void	redirect_freenode(void *arg)
{
	t_redirect	*redir;

	redir = arg;
	token_free(redir->target);
	free(arg);
}
