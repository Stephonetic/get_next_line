/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shannema <shannema@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 03:04:55 by shannema          #+#    #+#             */
/*   Updated: 2026/03/07 05:01:56 by shannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"

// static size_t	line_len(const char *buf)
// {
// 	if (!*buf || *buf == '\n')
// 	{
// 		if (*buf == '\n')
// 			return (1);
// 		return (0);
// 	}
// 	return (1 + line_len(buf + 1));
// }

// static char	*extract_and_carry(char *tmp, char *carry)
// {
// 	char	*line;
// 	size_t	len;

// 	if (!tmp || !tmp[0])
// 		return (NULL);
// 	len = line_len(tmp);
// 	line = malloc(len + 1);
// 	if (!line)
// 		return (NULL);
// 	ft_strlcpy(line, tmp, len + 1);
// 	ft_strlcpy(carry, tmp + len, BUFFER_SIZE + 1);
// 	return (line);
// }

// static char	*join_chunk(char *tmp, char *chunk, int n)
// {
// 	char	*old;

// 	chunk[n] = '\0';
// 	old = tmp;
// 	tmp = ft_strjoin(old, chunk);
// 	free(old);
// 	free(chunk);
// 	return (tmp);
// }

// static char	*fill_buffer(int fd, char *tmp, char *carry)
// {
// 	char	*chunk;
// 	int		n;

// 	if (!tmp || ft_strchr(tmp, '\n'))
// 		return (tmp);
// 	chunk = malloc(BUFFER_SIZE + 1);
// 	if (!chunk)
// 		return (NULL);
// 	n = read(fd, chunk, BUFFER_SIZE);
// 	if (n < 0)
// 	{
// 		free(chunk);
// 		free(tmp);
// 		carry[0] = '\0';
// 		return (NULL);
// 	}
// 	if (n == 0)
// 	{
// 		free(chunk);
// 		return (tmp);
// 	}
// 	return (fill_buffer(fd, join_chunk(tmp, chunk, n), carry));
// }

// char	*get_next_line(int fd)
// {
// 	static char	carry[BUFFER_SIZE + 1];
// 	char		*tmp;
// 	char		*line;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 	{
// 		carry[0] = '\0';
// 		return (NULL);
// 	}
// 	tmp = ft_strdup(carry);
// 	carry[0] = '\0';
// 	if (!tmp)
// 		return (NULL);
// 	tmp = fill_buffer(fd, tmp, carry);
// 	if (!tmp)
// 		return (NULL);
// 	line = extract_and_carry(tmp, carry);
// 	free(tmp);
// 	return (line);
// }

#include "get_next_line.h"

static size_t	line_len(const char *buf)
{
	size_t	len;

	len = 0;
	while (buf[len] && buf[len] != '\n')
		len++;
	if (buf[len] == '\n')
		len++;
	return (len);
}

static char	*extract_and_carry(char *tmp, char *carry)
{
	char	*line;
	size_t	len;

	if (!tmp || !tmp[0])
		return (NULL);
	len = line_len(tmp);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, tmp, len + 1);
	ft_strlcpy(carry, tmp + len, BUFFER_SIZE + 1);
	return (line);
}

static char	*join_chunk(char *tmp, char *chunk, int n)
{
	char	*old;

	chunk[n] = '\0';
	old = tmp;
	tmp = ft_strjoin(old, chunk);
	free(old);
	free(chunk);
	return (tmp);
}

static char	*read_next(int fd, char *tmp, char *carry, int *stop)
{
	char	*chunk;
	int		n;

	chunk = malloc(BUFFER_SIZE + 1);
	if (!chunk)
		return (NULL);
	n = read(fd, chunk, BUFFER_SIZE);
	if (n <= 0)
	{
		free(chunk);
		*stop = 1;
		if (n < 0)
		{
			free(tmp);
			carry[0] = '\0';
			return (NULL);
		}
		return (tmp);
	}
	return (join_chunk(tmp, chunk, n));
}

char	*get_next_line(int fd)
{
	static char	carry[BUFFER_SIZE + 1];
	char		*tmp;
	char		*line;
	int			stop;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		carry[0] = '\0';
		return (NULL);
	}
	tmp = ft_strdup(carry);
	carry[0] = '\0';
	if (!tmp)
		return (NULL);
	stop = 0;
	while (!stop && tmp && !ft_strchr(tmp, '\n'))
		tmp = read_next(fd, tmp, carry, &stop);
	if (!tmp)
		return (NULL);
	line = extract_and_carry(tmp, carry);
	free(tmp);
	return (line);
}
