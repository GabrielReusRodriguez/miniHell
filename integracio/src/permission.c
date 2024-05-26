/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permission.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:13:33 by abluis-m          #+#    #+#             */
/*   Updated: 2024/05/25 18:22:23 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "perm.h"
#include <unistd.h>

int	check_file_perm(char *fname)
{
	if (access(fname, F_OK) < 0)
		return (NO_FILE);
	else if (access(fname, R_OK) < 0)
		return (NO_READ);
	else if (access(fname, W_OK) < 0)
		return (NO_WRITE);
	return (PERM_OK);
}

int	check_cmd_perm(char *cname)
{
	if (access(cname, F_OK) < 0)
		return (NO_COMMAND);
	else if (access(cname, X_OK) < 0)
		return (NO_EXEC);
	return (PERM_OK);
}
