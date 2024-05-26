/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:00:54 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/25 18:45:42 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include "datatypes.h"
# include "minishell.h"

typedef struct s_route
{
	t_string	*folders;
	size_t		num_folders;		
}	t_route;

/*
	path.c
*/
bool		path_isrelative(t_string route);
t_string	path_getcwd(void);
int			path_chdir(t_string newdir, t_minishell *shell);

#endif