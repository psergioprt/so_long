/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_and_player_images_init_load_clean.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:23:23 by pauldos-          #+#    #+#             */
/*   Updated: 2024/07/24 09:25:00 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_game_player_images(t_game *game)
{
	game->player_images = (t_pl_im *)malloc(sizeof(t_pl_im));
	if (game->player_images == NULL)
	{
		ft_printf("Error\nFailed to allocate memory for player_images\n");
		exit(1);
	}
	game->player_images->img_player_up = NULL;
	game->player_images->img_player_down = NULL;
	game->player_images->img_player_left = NULL;
	game->player_images->img_player_right = NULL;
}

void	cleanup_player_images(t_game *game)
{
	if (game->player_images != NULL)
	{
		if (game->player_images->img_player_up)
			mlx_destroy_image(game->mlx, game->player_images->img_player_up);
		if (game->player_images->img_player_down)
			mlx_destroy_image(game->mlx, game->player_images->img_player_down);
		if (game->player_images->img_player_left)
			mlx_destroy_image(game->mlx, game->player_images->img_player_left);
		if (game->player_images->img_player_right)
			mlx_destroy_image(game->mlx, game->player_images->img_player_right);
	}
	free(game->player_images);
	game->player_images = NULL;
}

void	free_game_resources(t_game *game)
{
	int	i;

	i = 0;
	cleanup_mlx(game);
	cleanup_player_images(game);
	if (game->map != NULL)
	{
		while (i < game->line_count)
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
		game->map = NULL;
	}
	if (game->enemies != NULL)
	{
		free(game->enemies);
		game->enemies = NULL;
	}
}

void	cleanup_mlx(t_game *game)
{
	if (game->buffer)
		mlx_destroy_image(game->mlx, game->buffer);
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
	if (game->img_enemy)
		mlx_destroy_image(game->mlx, game->img_enemy);
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
		ft_printf("Error\nFailed to initialize MLX\n");
		exit(1);
	}
	game->window = mlx_new_window(game->mlx, game->max_line_length * TILE_SIZE, \
			game->line_count * TILE_SIZE, "so_long");
	if (!game->window)
	{
		ft_printf("Error\nFailed to create window\n");
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		exit(1);
	}
}
