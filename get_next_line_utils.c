/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shannema <shannema@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 03:14:42 by shannema          #+#    #+#             */
/*   Updated: 2026/03/05 04:08:44 by shannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	if (!s || !*s)
		return (0);
	return (1 + ft_strlen(s + 1));
}

char	*ft_strdup(const char *s)
{
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, ft_strlen(s) + 1);
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	if (*s == (char)c)
		return ((char *)s);
	if (*s == '\0')
		return (NULL);
	return (ft_strchr(s + 1, c));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	if (size > 1)
	{
		*dst = *src;
		if (*src)
			ft_strlcpy(dst + 1, src + 1, size - 1);
		else
			return (0);
	}
	else if (size == 1)
		*dst = '\0';
	if (!*src)
		return (0);
	return (ft_strlen(src));
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	if (s1)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	if (s2)
		len2 = ft_strlen(s2);
	else
		len2 = 0;
	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
		return (NULL);
	if (len1 > 0)
		ft_strlcpy(result, s1, len1 + 1);
	else
		result[0] = '\0';
	if (len2 > 0)
		ft_strlcpy(result + len1, s2, len2 + 1);
	return (result);
}
