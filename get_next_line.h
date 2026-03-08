/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shannema <shannema@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 03:14:47 by shannema          #+#    #+#             */
/*   Updated: 2026/03/08 22:51:55 by shannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

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

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(const char *s1, const char *s2);

#endif
