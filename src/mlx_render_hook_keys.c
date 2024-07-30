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

#include "so_long.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
	{
		game->should_exit = 1;
		return (0);
	}
	return (0);
}

static void	render_game_support_lines(t_game *game, int x, int y)
{
	char	tile;

	tile = game->map[y][x];
	if (tile == '1')
		mlx_put_image_to_window(game->mlx, game->window, game->img_wall, \
		x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == '0')
		mlx_put_image_to_window(game->mlx, game->window, game->img_road, \
		x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'P')
		mlx_put_image_to_window(game->mlx, game->window, game->img_player, \
		x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'E')
		mlx_put_image_to_window(game->mlx, game->window, game->img_exit, \
		x * TILE_SIZE, y * TILE_SIZE);
	else if (tile == 'C')
		mlx_put_image_to_window(game->mlx, game->window, game->img_item, \
		x * TILE_SIZE, y * TILE_SIZE);
}

static void	render_game(t_game *game)
{
	int		x;
	int		y;

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
}

static void	update_and_render(t_game *game)
{
	mlx_clear_window(game->mlx, game->window);
	render_game(game);
}

int	loop_hook(t_game *game)
{
	if (game->should_exit)
	{
		cleanup_mlx(game);
		mem_free(&game->map, game->line_count);
		exit(0);
	}
	update_and_render(game);
	return (0);
}
