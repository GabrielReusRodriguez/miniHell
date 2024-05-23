/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:46:18 by greus-ro          #+#    #+#             */
/*   Updated: 2024/05/12 21:15:22 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "tokens.h"

typedef struct s_redirect
{
	t_token	*type;
	t_token	*target;
}	t_redirect;

t_redirect	*redirect_new(void);
void		redirect_freenode(void *arg);

#endif