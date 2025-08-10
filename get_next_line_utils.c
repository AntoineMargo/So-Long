/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargolo <amargolo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:19:38 by amargolo          #+#    #+#             */
/*   Updated: 2024/12/05 12:19:38 by amargolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*array;
	size_t	total_size;
	char	*target;

	total_size = size * count;
	array = malloc(total_size);
	if (array == NULL)
		return (NULL);
	target = (char *)array;
	while (total_size > 0)
	{
		*target = 0;
		target++;
		total_size--;
	}
	return (array);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size)
{
	size_t	i;

	i = 0;
	if (dest_size == 0)
		return (0);
	while (i < dest_size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

char	*ft_substr(char const *s, long start, long len)
{
	char	*string;
	long	s_len;

	if (!s)
		return (NULL);
	s_len = 0;
	while (s[s_len])
		s_len++;
	if (start >= s_len)
		return (NULL);
	if (len == -1)
		len = s_len;
	if (start + len > s_len)
		len = s_len - start;
	string = ft_calloc(len + 1, sizeof(char));
	if (string == NULL)
		return (NULL);
	ft_strlcpy(string, &s[start], len + 1);
	return (string);
}

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}
