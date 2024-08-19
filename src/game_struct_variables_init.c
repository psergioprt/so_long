/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_struct_variables_init.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:47:23 by pauldos-          #+#    #+#             */
/*   Updated: 2024/07/24 11:47:56 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_game_struct_variables(t_game *game)
{
	game->line_count = 0;
	game->max_line_length = 0;
	game->map = NULL;
	game->player = 0;
	game->item = 0;
	game->exit_map = 0;
	game->mlx = NULL;
	game->window = NULL;
	game->img_player = NULL;
	game->img_wall = NULL;
	game->img_exit = NULL;
	game->img_road = NULL;
	game->img_item = NULL;
	game->player_x = 0;
	game->player_y = 0;
	game->total_items = 0;
	game->items_collected = 0;
	game->move_count = 0;
	game->new_x = 0;
	game->new_y = 0;
	game->buffer = NULL;
	game->buffer_data = NULL;
	game->img_width = TILE_SIZE;
	game->img_height = TILE_SIZE;
}
