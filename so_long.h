/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargolo <amargolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:18:15 by amargolo          #+#    #+#             */
/*   Updated: 2025/02/17 15:19:32 by amargolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <mlx.h>
# include "get_next_line.h"
# include "ft_printf.h"

# define GRASS_TILE		"assets/grass_empty.xpm"
# define DESERT_TILE	"assets/sand_empty.xpm"
# define CHARACTER		"assets/waterelemental.xpm"
# define WALL			"assets/stone_full.xpm"
# define STAIRS_UP		"assets/stairs_up.xpm"
# define STAIRS_DOWN	"assets/stairs_down.xpm"
# define IMG_DIMS	40

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*images[6];
	int			img_widths[6];
	int			img_heights[6];
	int			char_x;
	int			char_y;
	int			map_width;
	int			map_height;
	char		**map;
	char		**map_copy;
	int			entries_on_map;
	int			exits_on_map;
	int			exits_accessible;
	int			collectibles_on_map;
	int			collectibles_accessible;
	int			entry_x;
	int			entry_y;
	int			mov_count;

}	t_data;

int		ft_strlen_newline(const char *str);
char	*ft_strdup_newline(char *src);
int		build_map(t_data *data, char *map_address);
void	initialize_game_data(t_data *data);
int		validate_map_size(char *filename, t_data *data);
int		make_matrix(t_data *data, char ***matrix, char *map_address);
int		validate_map_enclosed(t_data *data);
int		validate_map_items(t_data *data);
void	set_starting_point(t_data *data, int y, int x);
int		validate_map_pathing(t_data *data);
void	fill(t_data *data, int y, int x);
void	free_matrix(char ***matrix, int max);
void	char_move(t_data *data, int y, int x);
int		on_keypress(int keysym, t_data *data);
void	load_images(t_data *data);
void	paint_tile(t_data *data, int j, int i);
void	paint_map_on_screen(t_data *data);
int		destroy_game(t_data *data);

#endif
