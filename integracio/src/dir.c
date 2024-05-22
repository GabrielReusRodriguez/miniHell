/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:37:17 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/22 00:11:31 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>

#include "datatypes.h"
#include "error_handler.h"
#include "libft.h"
#include "ptr.h"

/*
stat()  and  fstatat()  retrieve  information about the file pointed to by 
	pathname; the differences for fstatat() are de‐scribed below.
	
	All of these system calls return a stat structure, which contains the 
	following fields:

           struct stat {
               dev_t     st_dev;         // ID of device containing file 
               ino_t     st_ino;         // Inode number 
               mode_t    st_mode;        // File type and mode 
               nlink_t   st_nlink;       // Number of hard links 
               uid_t     st_uid;         // User ID of owner 
               gid_t     st_gid;         // Group ID of owner 
               dev_t     st_rdev;        // Device ID (if special file) 
               off_t     st_size;        // Total size, in bytes 
               blksize_t st_blksize;     // Block size for filesystem I/O 
               blkcnt_t  st_blocks;      // Number of 512B blocks allocated 


               struct timespec st_atim;  // Time of last access 
               struct timespec st_mtim;  // Time of last modification 
               struct timespec st_ctim;  // Time of last status change 

           #define st_atime st_atim.tv_sec      // Backward compatibility 
           #define st_mtime st_mtim.tv_sec
           #define st_ctime st_ctim.tv_sec
           };

*/


/*
S_ISREG() is a macro used to interpret the values in a stat-struct, as 
	returned from the system call stat(). It evaluates to true if the 
	argument(The st_mode member in struct stat) is a regular file. 
       Thus, to test for a regular file (for example), one could write:

           stat(pathname, &sb);
           if ((sb.st_mode & S_IFMT) == S_IFREG) {
               // Handle regular file 
           }

       Because tests of the above form are common, additional macros 
	   are defined by POSIX to allow the test of the file  type  in
       st_mode to be written more concisely:

           S_ISREG(m)  is it a regular file?

           S_ISDIR(m)  directory?

           S_ISCHR(m)  character device?

           S_ISBLK(m)  block device?

           S_ISFIFO(m) FIFO (named pipe)?

           S_ISLNK(m)  symbolic link?  (Not in POSIX.1-1996.)

           S_ISSOCK(m) socket?  (Not in POSIX.1-1996.)

       The preceding code snippet could thus be rewritten as:

           stat(pathname, &sb);
           if (S_ISREG(sb.st_mode)) {
               // Handle regular file 
           }
*/
/*
bool    dir_isdir(t_string path)
{
	struct stat	path_stat;
	
	if (stat(path, &path_stat) < 0)
	{
		if (errno == ENOMEM)
			error_system_crash("Error at memory malloc.\n");
		perror("Error");
		return (false);
	}
	return S_ISDIR(path_stat.st_mode);
}

static  size_t  dir_get_num_valid_parts(t_string *parts)
{
    size_t  num;
    size_t  i;

    num = 0;
    if (parts == NULL)
        return (0);
    while (parts[i] != NULL)
    {
        if (ft_strlen(parts[i]) > 0)
            num++;
        i++;
    }
    return (num);
}

//We remove the empty dirs liek /home//gabriel/ 
static t_string *dir_normalize_parts(t_string *parts)
{
    t_string    *norm_parts;
    size_t      i;
    size_t      total;

    total = dir_get_num_valid_parts(parts);
    norm_parts = safe_malloc((total + 1) * sizeof (char *));
    i = 0;
    total = 0;
    while (parts[i] != NULL)
    {
        if (ft_strlen(parts[i]) > 0)
        {
            norm_parts[total] = ft_strdup (parts[i]);
            ptr_check_malloc_return(norm_parts[total],"Error at memory malloc.\n");
            total++;
        }
        i++;
    }
    norm_parts[total] = NULL;
    return (norm_parts);    
}

t_string    *dir_getparts_of_path(t_string path)
{
    t_string    *parts;
    t_string    *norm_parts;
    
    parts = ft_split(path, '/');
    norm_parts = dir_normalize_parts(parts);
    ptr_freematrix(parts);
    return (norm_parts);
}
*/