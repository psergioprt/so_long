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

void	init_double_buffer(t_game *game) //added this function for double buffer
{
	game->buffer = mlx_new_image(game->mlx, game->max_line_length * TILE_SIZE, game->line_count *TILE_SIZE);
	if (!game->buffer)
	{
		ft_printf("Error\nFailed to create dloble buffer\n");
		exit (1);
	}
}

int	handle_items_and_exit(t_game *game)
{
	char		cur_element;

	cur_element = game->map[game->new_y][game->new_x];
	if (cur_element == 'C')
	{
		game->items_collected++;
		ft_printf("You have now %d items\n", game->items_collected);
	}
	if (cur_element == 'E')
	{
		if (game->items_collected == game->total_items)
		{
			ft_printf("Well done, you have completed the map\n");
			game->should_exit = 1;
			return (0);
		}
		else
			ft_printf("Not all items collected. %d to exit!\n", \
			game->total_items - game->items_collected);
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
		//mlx_loop_hook(game->mlx, loop_hook, game);
		//render_game(game);
	}
	return (0);
}

/*static void	render_game_support_lines(t_game *game, int x, int y, char *)
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

static void	render_enemy(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_enemies)
	{
		if (game->img_enemy)
			mlx_put_image_to_window(game->mlx, game->window, game->img_enemy, \
			game->enemies[i].enemy_x * TILE_SIZE, game->enemies[i].enemy_y * \
			TILE_SIZE);
		else
			ft_printf("Error\nEnemy image not loaded\n");
		i++;
	}
}*/

void draw_tile_to_buffer(t_game *game, void *image, int x, int y, char *buffer_data)
{
    char *tile_data;
    int tile_width, tile_height;
    int i, j;

    tile_data = mlx_get_data_addr(image, &tile_width, &tile_height, &game->img_endian);

    for (i = 0; i < TILE_SIZE; i++)
    {
        for (j = 0; j < TILE_SIZE; j++)
        {
            int buffer_pos = ((y * TILE_SIZE + i) * game->img_line_length + (x * TILE_SIZE + j) * (game->img_bits_per_pixel / 8));
            int tile_pos = (i * tile_width + j) * (game->img_bits_per_pixel / 8);

            // Copy pixel data from tile image to buffer
            *(int *)(buffer_data + buffer_pos) = *(int *)(tile_data + tile_pos);
        }
    }
}
static void render_game_support_lines(t_game *game, int x, int y, char *buffer_data)
{
    char tile;

    tile = game->map[y][x];
    if (tile == '1')
        draw_tile_to_buffer(game, game->img_wall, x, y, buffer_data);
    else if (tile == '0')
        draw_tile_to_buffer(game, game->img_road, x, y, buffer_data);
    else if (tile == 'P')
        draw_tile_to_buffer(game, game->img_player, x, y, buffer_data);
    else if (tile == 'E')
        draw_tile_to_buffer(game, game->img_exit, x, y, buffer_data);
    else if (tile == 'C')
        draw_tile_to_buffer(game, game->img_item, x, y, buffer_data);
}

static void render_enemy(t_game *game, char *buffer_data)
{
    int i;

    i = 0;
    while (i < game->num_enemies)
    {
        if (game->img_enemy)
            draw_tile_to_buffer(game, game->img_enemy, game->enemies[i].enemy_x, game->enemies[i].enemy_y, buffer_data);
        else
            ft_printf("Error\nEnemy image not loaded\n");
        i++;
    }
}

void	render_game(t_game *game)
{
	int		x;
	int		y;
	char	*buffer_data;

	buffer_data = mlx_get_data_addr(game->buffer, &game->img_bits_per_pixel, &game->img_line_length, &game->img_endian);

	y = 0;
	while (y < game->line_count)
	{
		x = 0;
		while (x < game->max_line_length)
		{
			render_game_support_lines(game, x, y, buffer_data);
			x++;
		}
		y++;
	}
	render_enemy(game, buffer_data);
	mlx_put_image_to_window(game->mlx, game->window, game->buffer, 0, 0);
}
