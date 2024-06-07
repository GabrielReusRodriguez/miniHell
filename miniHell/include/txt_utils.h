/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 23:13:36 by greus-ro          #+#    #+#             */
/*   Updated: 2024/06/08 00:38:08 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TXT_UTILS_H
# define TXT_UTILS_H

# include "datatypes.h"

t_string			text_join(t_string origin, t_string destiny);
unsigned long long	ft_atoull(const char *nbr);

#endif
