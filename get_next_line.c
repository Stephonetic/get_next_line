/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shannema <shannema@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 03:04:55 by shannema          #+#    #+#             */
/*   Updated: 2026/03/08 23:01:15 by shannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*grow_buf(char *buf, size_t *cap)
{
	char	*newbuf;

	*cap = *cap * 2 + BUFFER_SIZE;
	newbuf = malloc(*cap + 1);
	if (!newbuf)
	{
		free(buf);
		return (NULL);
	}
	ft_strlcpy(newbuf, buf, *cap + 1);
	free(buf);
	return (newbuf);
}

static char	*read_into(int fd, char *buf, size_t *len, size_t *cap)
{
	int	n;

	while (!ft_strchr(buf, '\n'))
	{
		if (*len + BUFFER_SIZE > *cap)
		{
			buf = grow_buf(buf, cap);
			if (!buf)
				return (NULL);
		}
		n = read(fd, buf + *len, BUFFER_SIZE);
		if (n < 0)
		{
			free(buf);
			return (NULL);
		}
		if (n == 0)
			return (buf);
		*len += n;
		buf[*len] = '\0';
	}
	return (buf);
}

static char	*make_line(char *buf, char *nl, char *carry)
{
	char	*line;
	size_t	len;

	if (!buf || !buf[0])
		return (NULL);
	if (nl)
	{
		ft_strlcpy(carry, nl + 1, BUFFER_SIZE + 1);
		len = (size_t)(nl - buf) + 1;
	}
	else
		len = ft_strlen(buf);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, buf, len + 1);
	return (line);
}

static char	*init_buf(char *carry, size_t *len, size_t *cap)
{
	char	*buf;

	*cap = BUFFER_SIZE;
	buf = malloc(*cap + 1);
	if (!buf)
		return (NULL);
	ft_strlcpy(buf, carry, *cap + 1);
	*len = ft_strlen(buf);
	carry[0] = '\0';
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	carry[BUFFER_SIZE + 1];
	char		*buf;
	char		*line;
	size_t		len;
	size_t		cap;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		carry[0] = '\0';
		return (NULL);
	}
	buf = init_buf(carry, &len, &cap);
	if (!buf)
		return (NULL);
	buf = read_into(fd, buf, &len, &cap);
	if (!buf)
		return (NULL);
	line = make_line(buf, ft_strchr(buf, '\n'), carry);
	free(buf);
	return (line);
}
