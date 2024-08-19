/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_images_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:23:23 by pauldos-          #+#    #+#             */
/*   Updated: 2024/07/24 09:25:00 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	output_clean_player_image_read_error(t_game *game)
{
	ft_printf("Error\nFailed to load player image\n");
	free_game_resources(game);
	free(game->img_player);
	exit(1);
}

static void	load_image_loading_fail_messages(t_game *game)
{
	if (!game->img_player || !game->img_wall || !game->img_item || \
			!game->img_exit || !game->img_road || !game->img_enemy)
	{
		if (!game->img_player)
			ft_printf("Error\nFailed to load player image\n");
		if (!game->img_wall)
			ft_printf("Error\nFailed to load wall image\n");
		if (!game->img_item)
			ft_printf("Error\nFailed to load item image\n");
		if (!game->img_exit)
			ft_printf("Error\nFailed to load exit image\n");
		if (!game->img_road)
			ft_printf("Error\nFailed to load road image\n");
		if (!game->img_enemy)
			ft_printf("Error\nFailed to load enemy image\n");
		free_game_resources(game);
		exit(1);
	}
}

void	if_img_player_not_null(t_game *game)
{
	if (game->img_player)
		mlx_destroy_image(game->mlx, game->img_player);
}

void	check_player_images(t_game *game)
{
	game->img_player = mlx_xpm_file_to_image(game->mlx, \
			IMG_PLAYER_LEFT, \
			&game->img_width, &game->img_height);
	if (!game->img_player)
		output_clean_player_image_read_error(game);
	if_img_player_not_null(game);
	game->img_player = mlx_xpm_file_to_image(game->mlx, \
			IMG_PLAYER_RIGHT, \
			&game->img_width, &game->img_height);
	if (!game->img_player)
		output_clean_player_image_read_error(game);
	if_img_player_not_null(game);
	game->img_player = mlx_xpm_file_to_image(game->mlx, \
			IMG_PLAYER_UP, \
			&game->img_width, &game->img_height);
	if (!game->img_player)
		output_clean_player_image_read_error(game);
	if_img_player_not_null(game);
	game->img_player = mlx_xpm_file_to_image(game->mlx, \
			IMG_PLAYER_DOWN, \
			&game->img_width, &game->img_height);
	if (!game->img_player)
		output_clean_player_image_read_error(game);
	if_img_player_not_null(game);
}

void	load_image(t_game *game)
{
	game->img_wall = mlx_xpm_file_to_image(game->mlx, WALL, \
	&game->img_width, &game->img_height);
	game->img_item = mlx_xpm_file_to_image(game->mlx, ITEM, \
	&game->img_width, &game->img_height);
	game->img_exit = mlx_xpm_file_to_image(game->mlx, EXIT, \
	&game->img_width, &game->img_height);
	game->img_road = mlx_xpm_file_to_image(game->mlx, ROAD, \
	&game->img_width, &game->img_height);
	game->img_enemy = mlx_xpm_file_to_image(game->mlx, ENEMY, \
	&game->img_width, &game->img_height);
	check_player_images(game);
	game->img_player = mlx_xpm_file_to_image(game->mlx, \
			IMG_PLAYER_DOWN, \
			&game->img_width, &game->img_height);
	load_image_loading_fail_messages(game);
}
