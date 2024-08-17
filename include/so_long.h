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

typedef struct s_enemy
{
	int	x;
	int	y;
	int	enemy_x;
	int	enemy_y;
	int	start_x;
	int	start_y;
	int	speed;
	int	direction;
}	t_enemy;

typedef struct s_player_image
{
	void *img_player_up;
	void *img_player_down;
	void *img_player_left;
	void *img_player_right;
}	t_player_image;

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
	int		img_width;
	int		img_height;
	void	*mlx;
	void	*window;
	char	**map;
	int		player_x;
	int		player_y;
	int		total_items;
	int		items_collected;
	int		move_count;
	int		new_x;
	int		new_y;
	int		enemy_x;
	int		enemy_y;
	int		direction;
	int		speed;
	void	*img_enemy;
	t_enemy	*enemies;
	int		lives;
	int		num_enemies;
	char	*buffer;
	char	*buffer_data;
	int		img_endian;
	int		img_line_length;
	int		img_bits_per_pixel;
	int		tile_width;
	int		tile_height;
	int		prev_player_x;
	int		prev_player_y;
	t_player_image	*player_images;

}	t_game;

typedef struct s_flood_fill_vars
{
	char	**map;
	int		rows;
	int		cols;
	int		**visited;
}	t_flood_fill_vars;

typedef struct s_draw_shape
{
	int		width;
	int		height;
	int		color;
	char	*item_str;
	char	*f_item_str;
	int		t_colr;
	char	*lives_str;
	int		lives_color;
}	t_draw_shape;

void	add_print_lines(char ***map, int fd);
void	mem_free(char ***map, int line_count, t_game *game);
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
int		window_esc_key_press(int keycode, t_game *game);
void	init_handle_enemy_vars(t_game *game);
void	move_enemies(t_game *game);
void	check_player_lives(t_game *game);
void	cleanup_enemy_array(t_game *game);
void	map_read(int fd, int *line_count, int *max_line_length);
void	init_double_buffer(t_game *game);
void	draw_tile_to_buffer(t_game *game, void *image, int x, int y);

void	init_game_player_images(t_game *game);
void	cleanup_player_images(t_game *game);
void	free_game_resources(t_game *game);
void	update_player_image(void *mlx, void **current_image, void *new_image);

#endif
