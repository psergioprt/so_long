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

static void	render_game(t_game *game);

void	draw_rectangle(t_game *game, t_draw_shape rectangle, int x, int y)
{
	int	i;
	int	j;
	
	i = x;
	while (i < x + rectangle.width)
	{
		j = y;
		while (j < y + rectangle.height)
		{
			mlx_pixel_put(game->mlx, game->window, i, j, rectangle.color);
			j++;
		}
		i++;
	}
}

void	display_move_count(t_game *game)
{
	t_draw_shape rectangle;
	char	*move_str;
	int	text_color;
	int	x;
	int	y;

	move_str = ft_itoa(game->move_count);
	if (!move_str)
	{
		fprintf(stderr, "Failed to allocate memory for move string\n");
		return;
	}
	text_color = 0xFFFFFF;
	rectangle.color = 0x000000;
	x = 30;
	y = 20;
	rectangle.width = 80;
	rectangle.height = 20;
	draw_rectangle(game, rectangle, x - 5, y - 15);
	mlx_string_put(game->mlx, game->window, x, y, text_color, "Moves: ");
	mlx_string_put(game->mlx, game->window, x + 40, y, text_color, move_str);
	free(move_str);
}

int loop_hook(t_game *game)
{
	if (game->should_exit)
	{
		cleanup_mlx(game);
		mem_free(&game->map, game->line_count);
		exit(0);
	}
	mlx_clear_window(game->mlx, game->window);
	render_game(game);
	display_move_count(game);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	int	new_x = game->player_x;
	int	new_y = game->player_y;

	if (keycode == ESC)
	{
		game->should_exit = 1;
		return (0);
	}
	if (keycode == UP_ARROW || keycode == KEY_W)
	{
		if (new_y > 0 && game->map[new_y - 1][new_x] != '1')
			new_y += -1;
	}
	else if (keycode == RIGHT_ARROW || keycode == KEY_D)
	{
		if (new_x < game->max_line_length && game->map[new_y][new_x + 1] != '1')
			new_x += 1;
	}
	else if (keycode == DOWN_ARROW || keycode == KEY_S)
	{
		if (new_y < game->line_count && game->map[new_y + 1][new_x] != '1')
			new_y += 1;
	}
	else if (keycode == LEFT_ARROW || keycode == KEY_A)
	{
		if (new_x > 0 && game->map[new_y][new_x - 1] != '1')
			new_x += -1;
	}
	if (new_x != game->player_x || new_y != game->player_y) {
        char curElement = game->map[new_y][new_x];
        static char prevElement = '0';

        if (curElement == 'C') {
            game->items_collected += 1;
            printf("You now have %d/%d items\n", game->items_collected, game->total_items);
        }

        // Check if moving to the exit
        if (curElement == 'E') {
            if (game->items_collected == game->total_items) {
                printf("Well done, you have completed the map\n");
                game->should_exit = 1;
                return (0);
            } else {
                printf("You still need to collect all items. Collected %d so far.\n", game->items_collected);
            }
        }

        game->move_count++;
        ft_printf("Move count %d\n", game->move_count);

        // Update the map with the new player position
        game->map[new_y][new_x] = 'P';

        // Restore previous position to 'E' if it was an exit
	game->map[game->player_y][game->player_x] = prevElement;

	// Remember what was under the player for the next move
        //prevElement = (curElement == 'C' || curElement == '0') ? '0' : curElement;

	if (curElement == 'C' || curElement == '0')
		prevElement = '0';
	else
		prevElement = curElement;

        // Update player coordinates
        game->player_x = new_x;
        game->player_y = new_y;
        printf("Player moved to [%d, %d]\n", new_y, new_x);

        // Request a redraw
        mlx_loop_hook(game->mlx, loop_hook, game);
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
