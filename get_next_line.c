/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargolo <amargolo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:49:35 by amargolo          #+#    #+#             */
/*   Updated: 2024/11/22 13:49:35 by amargolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*add_buffer_to_hold(char *hold, char *buffer)
{
	char	*new_hold;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = 0;
	len2 = 0;
	if (!hold)
		return (ft_substr(buffer, 0, -1));
	while (hold[len1])
		len1++;
	while (buffer[len2])
		len2++;
	new_hold = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!new_hold)
		return (ft_free(&hold));
	i = -1;
	while (++i < len1)
		new_hold[i] = hold[i];
	i = -1;
	while (++i < len2)
		new_hold[len1 + i] = buffer[i];
	ft_free(&hold);
	return (new_hold);
}

static char	*extract_data_from_fd(int fd, char *hold)
{
	char	*buffer;
	int		bytes_read;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		hold = add_buffer_to_hold(hold, buffer);
		if (!hold)
			return (ft_free(&buffer));
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
	{
		ft_free(&buffer);
		return (ft_free(&hold));
	}
	ft_free(&buffer);
	return (hold);
}

static char	*extract_last_line_from_hold(const char *hold)
{
	int		i;

	i = 0;
	while (hold[i] && hold[i] != '\n')
		i++;
	if (hold[i] == '\n')
		i++;
	return (ft_substr(hold, 0, i));
}

static char	*adjust_hold(char *hold)
{
	char			*newline_pos;
	char			*new_hold;
	unsigned int	len;
	unsigned int	old_len;

	newline_pos = ft_strchr(hold, '\n');
	if (!newline_pos)
		return (ft_free(&hold), NULL);
	len = newline_pos - hold + 1;
	old_len = 0;
	while (hold[old_len])
		old_len++;
	new_hold = ft_substr(hold, len, old_len - len);
	ft_free(&hold);
	if (!new_hold)
		return (NULL);
	return (new_hold);
}

char	*get_next_line(int fd)
{
	static char		*hold;
	char			*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	hold = extract_data_from_fd(fd, hold);
	if (!hold)
		return (NULL);
	line = extract_last_line_from_hold(hold);
	if (!line)
	{
		ft_free(&hold);
		return (NULL);
	}
	hold = adjust_hold(hold);
	return (line);
}
// # include <stdio.h>
// # include <fcntl.h>

// int main(void)
// {
// 	int		fd;
// 	char	*line;

// 	printf("\n---6 calls---\n");

// 	fd = open("There was once a cat who was also a wizard./n", O_RDONLY);
// 	if (fd < 0) {
// 		return (1);
// 	}
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	close(fd);

// 		return (0);
// }
