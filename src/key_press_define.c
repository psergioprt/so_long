/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_define.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 20:55:13 by pauldos-          #+#    #+#             */
/*   Updated: 2024/08/04 20:58:53 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	window_esc_key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
	{
		game->should_exit = 1;
		return (0);
	}
	return (0);
}

void	cursor_move_key_press(int keycode, t_game *game)
{
	if (keycode == UP_ARROW || keycode == KEY_W)
	{
		if (game->new_y > 0 && game->map[game->new_y - 1][game->new_x] != '1')
			game->new_y--;
	}
	else if (keycode == RIGHT_ARROW || keycode == KEY_D)
	{
		if (game->new_x < game->max_line_length - 1 && game->map[game->new_y] \
			[game->new_x + 1] != '1')
			game->new_x++;
	}
	else if (keycode == DOWN_ARROW || keycode == KEY_S)
	{
		if (game->new_y < game->line_count - 1 && game->map[game->new_y + 1] \
			[game->new_x] != '1')
			game->new_y++;
	}
	else if (keycode == LEFT_ARROW || keycode == KEY_A)
	{
		if (game->new_x > 0 && game->map[game->new_y][game->new_x - 1] != '1')
			game->new_x--;
	}
}
