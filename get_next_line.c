/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shannema <shannema@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 03:04:55 by shannema          #+#    #+#             */
/*   Updated: 2026/03/07 04:30:08 by shannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"

// static char	*_set_line(char *line_buffer)
// {
// 	char	*left_c;
// 	size_t	i;

// 	i = 0;
// 	while (line_buffer[i] && line_buffer[i] != '\n')
// 		i++;
// 	if (!line_buffer[i])
// 		return (NULL);
// 	left_c = ft_substr(line_buffer, i + 1,
// 			ft_strlen(line_buffer) - i);
// 	if (*left_c == 0)
// 	{
// 		free(left_c);
// 		left_c = NULL;
// 	}
// 	line_buffer[i + 1] = 0;
// 	return (left_c);
// }

// static char	*_fill_line_buffer(int fd, char *left_c)
// {
// 	char	*buffer;
// 	ssize_t	bytes_read;

// 	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (!buffer)
// 		return (NULL);
// 	bytes_read = 1;
// 	while (!ft_strchr(left_c, '\n') && bytes_read != 0)
// 	{
// 		bytes_read = read(fd, buffer, BUFFER_SIZE);
// 		if (bytes_read == -1)
// 		{
// 			free(buffer);
// 			return (NULL);
// 		}
// 		buffer[bytes_read] = 0;
// 		left_c = ft_strjoin(left_c, buffer);
// 	}
// 	free(buffer);
// 	return (left_c);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*left_c;
// 	char		*line;

// 	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
// 		return (NULL);
// 	left_c = _fill_line_buffer(fd, left_c);
// 	if (!left_c)
// 		return (NULL);
// 	line = ft_substr(left_c, 0,
// 			ft_strchr(left_c, '\n') - left_c + 1);
// 	left_c = _set_line(left_c);
// 	return (line);
// }

// #include "get_next_line.h"

// static char	*read_to_stash(int fd, char *stash)
// {
// 	char	*buf;
// 	ssize_t	bytes_read;

// 	if (ft_strchr(stash, '\n'))
// 		return (stash);
// 	buf = malloc(BUFFER_SIZE + 1);
// 	if (!buf)
// 		return (NULL);
// 	bytes_read = read(fd, buf, BUFFER_SIZE);
// 	if (bytes_read == 0)
// 	{
// 		free(buf);
// 		return (stash);
// 	}
// 	return (handle_read(fd, stash, buf, bytes_read));
// }

// static char	*handle_read(int fd, char *stash, char *buf, ssize_t bytes_read)
// {
// 	char	*tmp;

// 	if (bytes_read < 0)
// 	{
// 		free(buf);
// 		free(stash);
// 		return (NULL);
// 	}
// 	buf[bytes_read] = '\0';
// 	tmp = ft_strjoin(stash, buf);
// 	free(buf);
// 	free(stash);
// 	if (!tmp)
// 		return (NULL);
// 	return (read_to_stash(fd, tmp));
// }

// static size_t	line_len(const char *stash)
// {
// 	if (!*stash || *stash == '\n')
// 	{
// 		if (*stash == '\n')
// 			return (1);
// 		return (0);
// 	}
// 	return (1 + line_len(stash + 1));
// }

// static char	*extract_line(char *stash)
// {
// 	size_t	len;
// 	char	*line;

// 	if (!stash || !stash[0])
// 		return (NULL);
// 	len = line_len(stash);
// 	line = malloc(len + 1);
// 	if (!line)
// 		return (NULL);
// 	ft_strlcpy(line, stash, len + 1);
// 	return (line);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*stash;
// 	char		*line;
// 	char		*newline;
// 	char		*new_stash;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	stash = read_to_stash(fd, stash);
// 	if (!stash)
// 		return (NULL);
// 	line = extract_line(stash);
// 	newline = ft_strchr(stash, '\n');
// 	if (newline && *(newline + 1))
// 		new_stash = ft_strdup(newline + 1);
// 	else
// 		new_stash = NULL;
// 	free(stash);
// 	stash = new_stash;
// 	return (line);
// }

//new code
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

// static char	*fill_buffer(int fd, char *tmp, char *carry)
// {
// 	char	chunk[BUFFER_SIZE + 1];
// 	char	*old;
// 	int		n;

// 	if (ft_strchr(tmp, '\n'))
// 		return (tmp);
// 	n = read(fd, chunk, BUFFER_SIZE);
// 	if (n < 0)
// 	{
// 		free(tmp);
// 		carry[0] = '\0';
// 		return (NULL);
// 	}
// 	if (n == 0)
// 		return (tmp);
// 	chunk[n] = '\0';
// 	old = tmp;
// 	tmp = ft_strjoin(old, chunk);
// 	free(old);
// 	if (!tmp)
// 		return (NULL);
// 	return (fill_buffer(fd, tmp, carry));
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

//new code (final)

#include "get_next_line.h"

static size_t	line_len(const char *buf)
{
	if (!*buf || *buf == '\n')
	{
		if (*buf == '\n')
			return (1);
		return (0);
	}
	return (1 + line_len(buf + 1));
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

static char	*fill_buffer(int fd, char *tmp, char *carry)
{
	char	*chunk;
	int		n;

	if (!tmp || ft_strchr(tmp, '\n'))
		return (tmp);
	chunk = malloc(BUFFER_SIZE + 1);
	if (!chunk)
		return (NULL);
	n = read(fd, chunk, BUFFER_SIZE);
	if (n < 0)
	{
		free(chunk);
		free(tmp);
		carry[0] = '\0';
		return (NULL);
	}
	if (n == 0)
	{
		free(chunk);
		return (tmp);
	}
	return (fill_buffer(fd, join_chunk(tmp, chunk, n), carry));
}

char	*get_next_line(int fd)
{
	static char	carry[BUFFER_SIZE + 1];
	char		*tmp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		carry[0] = '\0';
		return (NULL);
	}
	tmp = ft_strdup(carry);
	carry[0] = '\0';
	if (!tmp)
		return (NULL);
	tmp = fill_buffer(fd, tmp, carry);
	if (!tmp)
		return (NULL);
	line = extract_and_carry(tmp, carry);
	free(tmp);
	return (line);
}
