/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shannema <shannema@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 03:14:42 by shannema          #+#    #+#             */
/*   Updated: 2026/03/01 04:13:53 by shannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	index;

	index = 0;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[index])
	{
		str[index] = s[index];
		index++;
	}
	str[index] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;

	len = ft_strlen(src);
	if (size > len + 1)
	{
		ft_memcpy(dst, src, len + 1);
	}
	else if (size)
	{
		ft_memcpy(dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	return (len);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	count_str_len1;
	size_t	count_str_len2;
	char	*result;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		count_str_len1 = 0;
	else
		count_str_len1 = ft_strlen(s1);
	if (!s2)
		count_str_len2 = 0;
	else
		count_str_len2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (count_str_len1 + count_str_len2 + 1));
	if (!result)
		return (NULL);
	if (count_str_len1 > 0)
		ft_strlcpy(result, s1, count_str_len1 + 1);
	else
		result[0] = '\0';
	if (count_str_len2 > 0)
		ft_strlcpy(result + count_str_len1, s2, count_str_len2 + 1);
	return (result);
}
