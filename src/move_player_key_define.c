/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_key_define.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 20:55:13 by pauldos-          #+#    #+#             */
/*   Updated: 2024/08/04 20:58:53 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player_up(t_game *game)
{
	void	*new_image;

	if (game->new_y > 0 && game->map[game->new_y - 1][game->new_x] != '1')
	{
		game->new_y--;
		new_image = mlx_xpm_file_to_image(game->mlx, \
				"./images/img_player_up.xpm", \
				&game->img_width, &game->img_height);
		if (game->img_player)
			mlx_destroy_image(game->mlx, game->img_player);
		game->img_player = new_image;
	}
}

void	move_player_right(t_game *game)
{
	void	*new_image;

	if (game->new_x < game->max_line_length - 1 && \
			game->map[game->new_y][game->new_x + 1] != '1')
	{
		game->new_x++;
		new_image = mlx_xpm_file_to_image(game->mlx, \
				"./images/img_player_right.xpm", \
				&game->img_width, &game->img_height);
		if (game->img_player)
			mlx_destroy_image(game->mlx, game->img_player);
		game->img_player = new_image;
	}
}

void	move_player_down(t_game *game)
{
	void	*new_image;

	if (game->new_y < game->line_count - 1 && game->map[game->new_y + 1] \
			[game->new_x] != '1')
	{
		game->new_y++;
		new_image = mlx_xpm_file_to_image(game->mlx, \
				"./images/img_player_down.xpm", \
				&game->img_width, &game->img_height);
		if (game->img_player)
			mlx_destroy_image(game->mlx, game->img_player);
		game->img_player = new_image;
	}
}

void	move_player_left(t_game *game)
{
	void	*new_image;

	if (game->new_x > 0 && game->map[game->new_y][game->new_x - 1] != '1')
	{
		game->new_x--;
		new_image = mlx_xpm_file_to_image(game->mlx, \
				"./images/img_player_left.xpm", \
				&game->img_width, &game->img_height);
		if (game->img_player)
			mlx_destroy_image(game->mlx, game->img_player);
		game->img_player = new_image;
	}
}

void	cursor_move_key_press(int keycode, t_game *game)
{
	if (keycode == UP_ARROW || keycode == KEY_W)
		move_player_up(game);
	else if (keycode == RIGHT_ARROW || keycode == KEY_D)
		move_player_right(game);
	else if (keycode == DOWN_ARROW || keycode == KEY_S)
		move_player_down(game);
	else if (keycode == LEFT_ARROW || keycode == KEY_A)
		move_player_left(game);
}
