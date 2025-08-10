/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargolo <amargolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:03:26 by amargolo          #+#    #+#             */
/*   Updated: 2025/02/17 15:19:36 by amargolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	build_map(t_data *data, char *map_address)
{
	initialize_game_data(data);
	if (!validate_map_size(map_address, data))
		return (ft_printf("Error\nThe map is not a rectangle.\n"), 0);
	if ((!make_matrix(data, &data->map, map_address))
		|| (!make_matrix(data, &data->map_copy, map_address)))
		return (ft_printf("Error\nThe matrixes failed to be created.\n"), 0);
	if (!validate_map_enclosed(data))
		return (ft_printf("Error\nThe map is not enclosed.\n"), 0);
	if (!validate_map_items(data))
	{
		ft_printf("Error\nMap does not have the necessary items ");
		ft_printf("or they are unrecognizable.\n");
		return (0);
	}
	if (!validate_map_pathing(data))
		return (ft_printf("Error\nNot all map items are accessible.\n"), 0);
	free_matrix(&data->map_copy, data->map_height);
	data->map_copy = NULL;
	return (1);
}

void	initialize_game_data(t_data *data)
{
	int	i;

	data->entries_on_map = 0;
	data->exits_on_map = 0;
	data->collectibles_on_map = 0;
	data->exits_accessible = 0;
	data->collectibles_accessible = 0;
	data->mov_count = 0;
	i = 0;
	data->map = NULL;
	data->map_copy = NULL;
	data->mlx = NULL;
	while (i < 6)
		data->images[i++] = NULL;
	data->map_width = -1;
	data->map_height = 0;
}

int	validate_map_size(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	int		validated;

	validated = 1;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (data->map_width == -1)
			data->map_width = ft_strlen_newline(line);
		else if (data->map_width != ft_strlen_newline(line))
			validated = 0;
		data->map_height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (validated)
		return (1);
	else
		return (0);
}

int	make_matrix(t_data *data, char ***matrix, char *map_address)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(map_address, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\n"), 0);
	*matrix = malloc(sizeof(char *) * (data->map_height + 1));
	if (!*matrix)
		return (close(fd), ft_printf("Error\n"), 0);
	(*matrix)[data->map_height] = NULL;
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		(*matrix)[i] = ft_strdup_newline(line);
		if (!(*matrix)[i])
			return (close(fd), free_matrix(matrix, i), ft_printf("Error\n"), 0);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	return (close(fd), 1);
}

int	validate_map_enclosed(t_data *data)
{
	int		i;
	int		j;

	j = 0;
	while (j < data->map_height)
	{
		i = 0;
		while (i < data->map_width)
		{
			if ((j == 0 || j == data->map_height - 1 || i == 0 
					|| i == data->map_width - 1) && (data->map[j][i] != '1'))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}
