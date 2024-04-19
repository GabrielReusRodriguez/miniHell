/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abluis-m <abluis-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:46:39 by abluis-m          #+#    #+#             */
/*   Updated: 2024/01/04 20:53:04 by abluis-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 80
# endif

size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
char	*ft_free(char **str);

#endif
