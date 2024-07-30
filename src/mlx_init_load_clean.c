/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_load_clean.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:23:23 by pauldos-          #+#    #+#             */
/*   Updated: 2024/07/24 09:25:00 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_image_loading_fail_messages(t_game *game)
{
	if (!game->img_player || !game->img_wall || !game->img_item || \
		!game->img_exit || !game->img_road)
	{
		if (!game->img_player)
			ft_printf("Failed to load player image\n");
		if (!game->img_wall)
			ft_printf("Failed to load wall image\n");
		if (!game->img_item)
			ft_printf("Failed to load item image\n");
		if (!game->img_exit)
			ft_printf("Failed to load exit image\n");
		if (!game->img_road)
			ft_printf("Failed to load road image\n");
		cleanup_mlx(game);
		mem_free(&game->map, game->line_count);
		exit(1);
	}
}

void	load_image(t_game *game)
{
	game->img_player = mlx_xpm_file_to_image(game->mlx, "./images/player.xpm", \
	&game->img_width, &game->img_height);
	game->img_wall = mlx_xpm_file_to_image(game->mlx, "./images/wall.xpm", \
	&game->img_width, &game->img_height);
	game->img_item = mlx_xpm_file_to_image(game->mlx, "./images/item.xpm", \
	&game->img_width, &game->img_height);
	game->img_exit = mlx_xpm_file_to_image(game->mlx, "./images/exit.xpm", \
	&game->img_width, &game->img_height);
	game->img_road = mlx_xpm_file_to_image(game->mlx, "./images/road.xpm", \
	&game->img_width, &game->img_height);
	load_image_loading_fail_messages(game);
}

void	cleanup_mlx(t_game *game)
{
	if (game->img_player)
		mlx_destroy_image(game->mlx, game->img_player);
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_item)
		mlx_destroy_image(game->mlx, game->img_item);
	if (game->img_exit)
		mlx_destroy_image(game->mlx, game->img_exit);
	if (game->img_road)
		mlx_destroy_image(game->mlx, game->img_road);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf("Failed to initialize MLX\n");
		exit(1);
	}
	game->window = mlx_new_window(game->mlx, game->max_line_length * TILE_SIZE, \
			game->line_count * TILE_SIZE, "so_long");
	if (!game->window)
	{
		ft_printf("Failed to create window\n");
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		exit(1);
	}
}
