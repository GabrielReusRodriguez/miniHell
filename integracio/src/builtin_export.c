/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:08:45 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/02 22:12:01 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
https://www.computerhope.com/unix/bash/export.htm

On Unix-like operating systems, export is a builtin command of the Bash shell. It designates specified variables and functions to be passed to child processes.

Normally, when you run a command at the bash prompt, a dedicated process is created with its own environment, exclusively for running your command. Any variables and functions you defined before running the command are not shared with new processes — unless you explicitly mark them with export.

Syntax 
export [-f] [-n] [name[=value] ...]

*/