/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_stat.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 07:46:30 by greus-ro          #+#    #+#             */
/*   Updated: 2024/04/20 18:27:21 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	minishell_stat_init(t_minishell_status *stat)
{
	stat->return_status = EXIT_SUCCESS;
	stat->run = true;
}

void	minishell_stat_destroy(t_minishell_status *stat)
{
	(void)stat;
}
