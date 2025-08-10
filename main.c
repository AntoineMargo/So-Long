/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargolo <amargolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:06:52 by amargolo          #+#    #+#             */
/*   Updated: 2025/02/14 17:46:24 by amargolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_images(t_data *data)
{
	data->images[0] = mlx_xpm_file_to_image(data->mlx, 
			CHARACTER, &data->img_widths[0], &data->img_heights[0]);
	data->images[1] = mlx_xpm_file_to_image(data->mlx, 
			GRASS_TILE, &data->img_widths[1], &data->img_heights[1]);
	data->images[2] = mlx_xpm_file_to_image(data->mlx, 
			DESERT_TILE, &data->img_widths[2], &data->img_heights[2]);
	data->images[3] = mlx_xpm_file_to_image(data->mlx, 
			WALL, &data->img_widths[3], &data->img_heights[3]);
	data->images[4] = mlx_xpm_file_to_image(data->mlx, 
			STAIRS_UP, &data->img_widths[4], &data->img_heights[4]);
	data->images[5] = mlx_xpm_file_to_image(data->mlx, 
			STAIRS_DOWN, &data->img_widths[5], &data->img_heights[5]);
}

void	paint_tile(t_data *data, int j, int i)
{
	if (data->map[j][i] == '1')
		mlx_put_image_to_window(data->mlx, data->win,
			data->images[3], i * IMG_DIMS, j * IMG_DIMS);
	if (data->map[j][i] == '0')
		mlx_put_image_to_window(data->mlx, data->win,
			data->images[1], i * IMG_DIMS, j * IMG_DIMS);
	if (data->map[j][i] == 'C')
		mlx_put_image_to_window(data->mlx, data->win,
			data->images[2], i * IMG_DIMS, j * IMG_DIMS);
	if (data->map[j][i] == 'P')
		mlx_put_image_to_window(data->mlx, data->win,
			data->images[4], i * IMG_DIMS, j * IMG_DIMS);
	if (data->map[j][i] == 'E')
		mlx_put_image_to_window(data->mlx, data->win,
			data->images[5], i * IMG_DIMS, j * IMG_DIMS);
}

void	paint_map_on_screen(t_data *data)
{
	int		i;
	int		j;

	j = 0;
	while (j < data->map_height)
	{
		i = 0;
		while (i < data->map_width)
		{
			paint_tile(data, j, i);
			i++;
		}
		j++;
	}
}

int	destroy_game(t_data *data)
{
	int	i;

	if (data->mlx)
	{
		i = 0;
		while (i < 6)
		{
			if (data->images[i])
				mlx_destroy_image(data->mlx, data->images[i]);
			i++;
		}
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free_matrix(&data->map, data->map_height);
	if (data->map_copy)
		free_matrix(&data->map_copy, data->map_height);
	exit(0);
}

int	main(int arc, char **arv)
{
	t_data	data;

	if (arc != 2)
		return (ft_printf("Error\nOne argument needed.\n"), 1);
	if (!build_map(&data, arv[1]))
		return (destroy_game(&data), 1);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (ft_printf("Error\nMlx failed.\n"), destroy_game(&data), 1);
	data.win = mlx_new_window(data.mlx, data.map_width * IMG_DIMS,
			data.map_height * IMG_DIMS, "Fertilize the land!");
	if (!data.win)
		return (free(data.mlx),
			ft_printf("Error\nWindow did not materialize.\n"), 1);
	(void)data.win;
	load_images(&data);
	paint_map_on_screen(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.images[0],
		data.char_x * IMG_DIMS, data.char_y * IMG_DIMS);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, &on_keypress, &data);
	mlx_hook(data.win, DestroyNotify, 0, &destroy_game, &data);
	mlx_loop(data.mlx);
	destroy_game(&data);
	return (0);
}
