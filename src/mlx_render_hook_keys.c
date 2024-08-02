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
	int	new_x = game->player_x;
	int	new_y = game->player_y;
	int	previous_x = game->player_x;
	int	previous_y = game->player_y;

	if (keycode == 65307)
	{
		game->should_exit = 1;
		return (0);
	}
	if (keycode == 65362 || keycode == 119) //up
	{
		if (new_y > 0 && game->map[new_y - 1][new_x] != '1')
			new_y += -1;
	}
	else if (keycode == 65363 || keycode == 100) //right
	{
		printf("Player: %c -> map[%d][%d]\n", game->map[new_y][new_x], new_y, new_x);
		if (new_x < game->max_line_length && game->map[new_y][new_x + 1] != '1')
			new_x += 1;
	}
	else if (keycode == 65364 || keycode == 115) //down
	{
		if (new_y < game->line_count && game->map[new_y + 1][new_x] != '1')
			new_y += 1;
	}
	else if (keycode == 65361 || keycode == 97) //left
	{
		if (new_x > 0 && game->map[new_y][new_x - 1] != '1')
			new_x += -1;
	}

	game->player_x = new_x;
	game->player_y = new_y;
	if (game->map[previous_y][previous_x] == 'P')
		game->map[previous_y][previous_x] = '0';
	if (game->map[new_y][new_x] == 'C')
	{
		game->items_collected += 1;
		printf("You now have %d/%d items\n", game->items_collected, game->total_items);
	}
	if (game->map[new_y][new_x] == 'E')
	{
		game->map[new_y][new_x] = 'P';
		if (game->items_collected == game->total_items)
		{
			ft_printf("Well done, you have completed the map\n");
			game->should_exit = 1;
		}
		else
		{
			game->map[previous_y][previous_x] = 'E';
			ft_printf("So far you have only collected %d items\n", game->items_collected);
			return (0);
		}
	}
	game->map[new_y][new_x] = 'P';
	previous_x = new_x;
	previous_y = new_y;
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
