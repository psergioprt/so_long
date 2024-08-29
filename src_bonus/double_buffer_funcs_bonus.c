/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_buffer_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:56:32 by pauldos-          #+#    #+#             */
/*   Updated: 2024/08/12 20:21:34 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/so_long_bonus.h"

void	init_double_buffer(t_game *game)
{
	game->buffer = mlx_new_image(game->mlx, game->max_line_length * TILE_SIZE, \
			game->line_count * TILE_SIZE);
	if (!game->buffer)
	{
		ft_printf("Error\nFailed to create double buffer\n");
		exit (1);
	}
	game->img_endian = 0;
	game->img_bits_per_pixel = 32;
}

void	draw_tile_to_buffer(t_game *game, void *image, int x, int y)
{
	char	*tile_data;
	int		buffer_pos;
	int		tile_pos;
	int		img_line_length;
	int		pos;

	pos = 0;
	tile_data = mlx_get_data_addr(image, &game->img_bits_per_pixel, \
	&img_line_length, &game->img_endian);
	while (pos < TILE_SIZE * TILE_SIZE)
	{
		buffer_pos = ((y * TILE_SIZE + pos / TILE_SIZE) * game->img_line_length \
		+ (x * TILE_SIZE + pos % TILE_SIZE) * (game->img_bits_per_pixel / 8));
		tile_pos = (pos / TILE_SIZE * game->img_width + pos % TILE_SIZE) * \
		(game->img_bits_per_pixel / 8);
		*(int *)(game->buffer_data + buffer_pos) = *(int *)(tile_data + \
		tile_pos);
		pos++;
	}
}
