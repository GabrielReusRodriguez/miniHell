/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_stat.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 07:46:30 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/16 07:47:47 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_minishell.h"

void		ft_minishell_stat_init(t_minishell_status *stat)
{
	stat->return_status = EXIT_SUCCESS;
	stat->run = TRUE;
}

void		ft_minishell_stat_destroy(t_minishell_status *stat)
{
	(void)stat;
}
