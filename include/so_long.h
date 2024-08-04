/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:47:23 by pauldos-          #+#    #+#             */
/*   Updated: 2024/07/24 11:47:56 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include "../util_funcs/ft_printf/ft_printf.h"
# include "../util_funcs/Libft/libft.h"
# include "../util_funcs/get_next_line/get_next_line.h"
# include "mlx.h"

# define TILE_SIZE 32
# define ESC 65307
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define DESTROY_NOTIFY 17

typedef struct s_game
{
	int		line_count;
	int		max_line_length;
	int		player;
	int		item;
	int		exit_map;
	void	*img_player;
	void	*img_wall;
	void	*img_exit;
	void	*img_road;
	void	*img_item;
	int	img_width;
	int	img_height;
	void	*mlx;
	void	*window;
	char	**map;
	int	should_exit;
	int		player_x;
	int		player_y;
	int		total_items;
	int		items_collected;
	int		move_count;
	int		new_x;
	int		new_y;
}	t_game;

typedef struct s_flood_fill_vars
{
	char	**map;
	int		rows;
	int		cols;
	int		**visited;
}t_flood_fill_vars;

typedef struct s_draw_shape
{
	int		width;
	int		height;
	int		color;
	char	*item_str;
	char	*f_item_str;
	int		t_colr;
}t_draw_shape;

void	add_print_lines(char ***map, int fd);
void	mem_free(char ***map, int line_count);
int		map_mem_allocate(char ***map, int fd, int line_ct, int max_line_lth);
bool	check_rectangle(char **map, int line_count);
bool	validate_map(char **map, int line_count, t_game *game);
void	init_game_struct_variables(t_game *game);
void	init_mlx(t_game *game);
void	cleanup_mlx(t_game *game);
int		loop_hook(t_game *game);
int		update_map_moves(int keycode, t_game *game);
void	init_mlx(t_game *game);
void	load_image(t_game *game);
void	validate_reachability(t_game *game);
void	free_flood_mem(t_game *game, t_flood_fill_vars *f, int *flag);
int		close_window(t_game *game);
bool	check_map_elements(char **map, int line_count, t_game *game);
void	render_game(t_game *game);
void	cursor_move_key_press(int keycode, t_game *game);
int	window_esc_key_press(int keycode, t_game *game);

#endif
