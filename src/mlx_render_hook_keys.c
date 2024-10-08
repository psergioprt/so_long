/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_hook_keys.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:33:21 by pauldos-          #+#    #+#             */
/*   Updated: 2024/07/30 14:34:18 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	handle_items_and_exit(t_game *game)
{
	char		cur_element;

	cur_element = game->map[game->new_y][game->new_x];
	if (cur_element == 'C')
		game->items_collected++;
	if (cur_element == 'E')
	{
		if (game->items_collected == game->total_items)
		{
			close_window(game);
			return (0);
		}
	}
	game->move_count++;
	ft_printf("Move count %d\n", game->move_count);
	return (0);
}

int	update_map_moves(int keycode, t_game *game)
{
	char		cur_element;
	static char	prev_element = '0';

	window_esc_key_press(keycode, game);
	game->new_x = game->player_x;
	game->new_y = game->player_y;
	cursor_move_key_press(keycode, game);
	if (game->new_x != game->player_x || game->new_y != game->player_y)
	{
		cur_element = game->map[game->new_y][game->new_x];
		handle_items_and_exit(game);
		game->map[game->new_y][game->new_x] = 'P';
		game->map[game->player_y][game->player_x] = prev_element;
		game->player_x = game->new_x;
		game->player_y = game->new_y;
		if (cur_element == 'C' || cur_element == '0')
			prev_element = '0';
		else
			prev_element = cur_element;
	}
	return (0);
}

static void	render_game_support_lines(t_game *game, int x, int y)
{
	char	tile;

	tile = game->map[y][x];
	if (tile == '1')
		draw_tile_to_buffer(game, game->img_wall, x, y);
	else if (tile == '0')
		draw_tile_to_buffer(game, game->img_road, x, y);
	else if (tile == 'P')
		draw_tile_to_buffer(game, game->img_player, x, y);
	else if (tile == 'E')
		draw_tile_to_buffer(game, game->img_exit, x, y);
	else if (tile == 'C')
		draw_tile_to_buffer(game, game->img_item, x, y);
}

void	render_game(t_game *game)
{
	int		x;
	int		y;

	game->buffer_data = mlx_get_data_addr(game->buffer, \
			&game->img_bits_per_pixel, &game->img_line_length, \
			&game->img_endian);
	y = 0;
	while (y < game->line_count)
	{
		x = 0;
		while (x < game->max_line_length)
		{
			render_game_support_lines(game, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->buffer, 0, 0);
}
