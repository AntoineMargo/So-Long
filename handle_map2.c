/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargolo <amargolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:06:30 by amargolo          #+#    #+#             */
/*   Updated: 2025/02/14 17:15:25 by amargolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_map_items(t_data *data)
{
	int		i;
	int		j;

	j = 0;
	while (j < data->map_height)
	{
		i = 0;
		while (i < data->map_width)
		{
			if (data->map[j][i] == 'P')
				set_starting_point(data, j, i);
			else if (data->map[j][i] == 'E')
				data->exits_on_map++;
			else if (data->map[j][i] == 'C')
				data->collectibles_on_map++;
			else if (!(data->map[j][i] == '0' || data->map[j][i] == '1'))
				return (0);
			i++;
		}
		j++;
	}
	if ((data->entries_on_map != 1) || (data->exits_on_map != 1)
		|| (data->collectibles_on_map < 1))
		return (0);
	return (1);
}

void	set_starting_point(t_data *data, int y, int x)
{
	data->entry_y = y;
	data->entry_x = x;
	data->entries_on_map++;
	data->char_y = y;
	data->char_x = x;
}

int	validate_map_pathing(t_data *data)
{
	fill(data, data->entry_y, data->entry_x);
	if (data->exits_accessible != data->exits_on_map)
		return (0);
	if (data->collectibles_accessible != data->collectibles_on_map)
		return (0);
	return (1);
}

void	fill(t_data *data, int y, int x)
{
	if ((x < 0) || (y < 0) || (x >= data->map_width) || (y >= data->map_height))
		return ;
	if ((data->map_copy[y][x] == '1' ) || (data->map_copy[y][x] == 'X'))
		return ;
	else if (data->map_copy[y][x] == 'E')
		data->exits_accessible++;
	else if (data->map_copy[y][x] == 'C')
		data->collectibles_accessible++;
	data->map_copy[y][x] = 'X';
	fill(data, y, x + 1);
	fill(data, y, x - 1);
	fill(data, y + 1, x);
	fill(data, y - 1, x);
}

void	free_matrix(char ***matrix, int max)
{
	int		i;

	if (!*matrix)
		return ;
	i = 0;
	while (i < max)
	{
		free((*matrix)[i]);
		i++;
	}
	free(*matrix);
}
