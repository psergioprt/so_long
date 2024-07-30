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
}	t_game;

void	add_print_lines(char ***map, int fd);
void	mem_free(char ***map, int line_count);
int		map_mem_allocate(char ***map, int fd, int line_ct, int max_line_lth);
bool	check_rectangle(char **map, int line_count);
bool	validate_map(char **map, int line_count);
void	init_game(t_game *game);
void	init_mlx(t_game *game);
void	cleanup_mlx(t_game *game);
int		loop_hook(t_game *game);
int		key_press(int keycode, t_game *game);
void	init_mlx(t_game *game);
void	load_image(t_game *game);


#endif
