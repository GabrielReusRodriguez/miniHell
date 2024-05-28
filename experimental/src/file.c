/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:46:37 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/29 00:35:37 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>

#include "datatypes.h"
#include "error_handler.h"

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
bool	file_isfile(t_string path)
{
	struct stat	path_stat;	

	if (stat(path, &path_stat) < 0)
	{
		if (errno == ENOMEM)
			error_system_crash("Error at memory malloc.\n");
		perror("Error");
		return (false);
	}
	return (S_ISREG(path_stat.st_mode));
}
*/