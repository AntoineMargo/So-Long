/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargolo <amargolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:22:22 by amargolo          #+#    #+#             */
/*   Updated: 2025/02/14 15:40:45 by amargolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen_newline(const char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] && str[i] != '\n')
			i++;
		return (i);
	}
	return (0);
}

char	*ft_strdup_newline(char *src)
{
	char	*dup;
	size_t	i;

	dup = malloc(ft_strlen_newline(src) + 1);
	if (!dup)
		return (0);
	i = 0;
	while (src[i] && src[i] != '\n')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
