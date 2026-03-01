/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shannema <shannema@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 03:14:47 by shannema          #+#    #+#             */
/*   Updated: 2026/03/01 03:21:28 by shannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

// # if defined(__APPLE__)
// #  define PTRNULL "0x0"
// #  define PTRNULL_LEN 3
// # elif defined(__linux__)
// #  define PTRNULL "(nil)"
// #  define PTRNULL_LEN 5
// # else
// #  define PTRNULL "(nil)"
// #  define PTRNULL_LEN 5
// # endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);

char	*get_next_line(int fd);

#endif