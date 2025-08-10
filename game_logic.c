/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargolo <amargolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:09:15 by amargolo          #+#    #+#             */
/*   Updated: 2025/02/17 15:19:35 by amargolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	char_move(t_data *data, int y, int x)
{
	if (data->map[data->char_y + y][data->char_x + x] == '1')
		return ;
	else if (data->map[data->char_y + y][data->char_x + x] == 'E'
		&& data->collectibles_accessible == 0)
	{
		ft_printf("\nGame won!!!\nGame won!!!\nGame won!!!\n\n");
		destroy_game(data);
	}
	else if (data->map[data->char_y + y][data->char_x + x] == 'C')
	{
		data->collectibles_accessible--;
		data->map[data->char_y + y][data->char_x + x] = '0';
	}
	data->char_y += y;
	data->char_x += x;
	data->mov_count++;
}

int	on_keypress(int keysym, t_data *data)
{
	int	x;
	int	y;

	x = data->char_x;
	y = data->char_y;
	if (keysym == 65307)
		destroy_game(data);
	else if (keysym == 97)
		char_move(data, 0, -1);
	else if (keysym == 100)
		char_move(data, 0, +1);
	else if (keysym == 119)
		char_move(data, -1, 0);
	else if (keysym == 115)
		char_move(data, +1, 0);
	mlx_clear_window(data->mlx, data->win);
	paint_map_on_screen(data);
	mlx_put_image_to_window(data->mlx, data->win, data->images[0],
		data->char_x * IMG_DIMS, data->char_y * IMG_DIMS);
	if (x != data->char_x || y != data->char_y)
		ft_printf("Movement count: %i \n", data->mov_count);
	return (0);
}
