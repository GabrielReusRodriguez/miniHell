/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:01:20 by abluis-m          #+#    #+#             */
/*   Updated: 2024/01/04 20:56:17 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 80
# endif
# ifndef FD_MAX
#  define FD_MAX 4096 
# endif

size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
char	*ft_free(char **str);

#endif
