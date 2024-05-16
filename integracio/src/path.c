/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:02:31 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/16 21:13:41 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#include "datatypes.h"
#include "libft.h"
#include "minishell.h"
#include "error_handler.h"

/*
	If it starts with / it is an absolute route else relative route.
*/
bool    path_isrelative(t_string route)
{
	if (route[0] == '/')
		return (false);
	return (true);

}

/*
 The getcwd() function copies an absolute pathname of the current working directory to the array pointed to by buf, which is
       of length size.

       If  the length of the absolute pathname of the current working directory, including the terminating null byte, exceeds size
       bytes, NULL is returned, and errno is set to ERANGE; an application should check for this error, and allocate a larger buf‐
       fer if necessary.

       As  an  extension to the POSIX.1-2001 standard, glibc's getcwd() allocates the buffer dynamically using malloc(3) if buf is
       NULL.  In this case, the allocated buffer has the length size unless size is zero, when buf is allocated as big  as  neces‐
       sary.  The caller should free(3) the returned buffer.

	   ERRORS
       EACCES Permission to read or search a component of the filename was denied.

       EFAULT buf points to a bad address.

       EINVAL The size argument is zero and buf is not a null pointer.

       EINVAL getwd(): buf is NULL.

       ENAMETOOLONG
              getwd(): The size of the null-terminated absolute pathname string exceeds PATH_MAX bytes.

       ENOENT The current working directory has been unlinked.

       ENOMEM Out of memory.

       ERANGE The size argument is less than the length of the absolute pathname of the working directory, including the terminat‐
              ing null byte.  You need to allocate a bigger array and try again.

*/
t_string	path_getcwd(void)
{
	t_string    path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		if (errno == ENOMEM)
			error_system_crash("Error at memory malloc.\n");
		perror("Error");
	}
	return (path);	
}

void    path_chdir(t_string newdir, t_minishell *shell)
{
	t_string	cwd;
	t_string	abs_path;
	
	cwd = shell->cfg.pwd;
	if (path_isrelative(newdir))
	{
		(void)cwd;
	}
	else
	{
		abs_path = ft_strdup(newdir);
	}
	free (shell->cfg.pwd);
	shell->cfg.pwd = abs_path;


}
