/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:00:54 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/23 18:13:04 by gabriel          ###   ########.fr       */
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
void		path_isrelative(t_string route);
t_string	path_getcwd(void);
int			path_chdir(t_string newdir, t_minishell *shell);

#endif