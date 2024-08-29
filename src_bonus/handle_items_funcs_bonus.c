/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_item_etc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:23:23 by pauldos-          #+#    #+#             */
/*   Updated: 2024/07/24 09:25:00 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/so_long_bonus.h"

void	cleanup_mlx_items(t_game *game)
{
	int	i;

	i = 0;
	while (i < ITEM_LOOP_IMAGES_NUM)
	{
		if (game->img_item[i])
		{
			mlx_destroy_image(game->mlx, game->img_item[i]);
			game->img_item[i] = NULL;
		}
		i++;
	}
}

void	items_frame_loop(t_game *game)
{
	static int	frame_counter = 0;
	int			frame_delay;

	frame_delay = 5;
	frame_counter++;
	if (frame_counter >= frame_delay)
	{
		frame_counter = 0;
		game->current_frame++;
		if (game->current_frame >= ITEM_LOOP_IMAGES_NUM)
			game->current_frame = 0;
	}
}

void	load_image_item_loading_fail_messages(t_game *game)
{
	int	i;

	i = 0;
	while (i < ITEM_LOOP_IMAGES_NUM)
	{
		if (!game->img_item[i])
		{
			ft_printf("Error\nFailed to load item image %d\n", i + 1);
			free_game_resources(game);
			exit(1);
		}
		i++;
	}
}

void	load_image_item_2(t_game *game)
{
	game->img_item[10] = mlx_xpm_file_to_image(game->mlx, ITEM11, \
	&game->img_width, &game->img_height);
	game->img_item[11] = mlx_xpm_file_to_image(game->mlx, ITEM12, \
	&game->img_width, &game->img_height);
	game->img_item[12] = mlx_xpm_file_to_image(game->mlx, ITEM13, \
	&game->img_width, &game->img_height);
	game->img_item[13] = mlx_xpm_file_to_image(game->mlx, ITEM14, \
	&game->img_width, &game->img_height);
}

void	load_image_item(t_game *game)
{
	game->img_item[0] = mlx_xpm_file_to_image(game->mlx, ITEM1, \
	&game->img_width, &game->img_height);
	game->img_item[1] = mlx_xpm_file_to_image(game->mlx, ITEM2, \
	&game->img_width, &game->img_height);
	game->img_item[2] = mlx_xpm_file_to_image(game->mlx, ITEM3, \
	&game->img_width, &game->img_height);
	game->img_item[3] = mlx_xpm_file_to_image(game->mlx, ITEM4, \
	&game->img_width, &game->img_height);
	game->img_item[4] = mlx_xpm_file_to_image(game->mlx, ITEM5, \
	&game->img_width, &game->img_height);
	game->img_item[5] = mlx_xpm_file_to_image(game->mlx, ITEM6, \
	&game->img_width, &game->img_height);
	game->img_item[6] = mlx_xpm_file_to_image(game->mlx, ITEM7, \
	&game->img_width, &game->img_height);
	game->img_item[7] = mlx_xpm_file_to_image(game->mlx, ITEM8, \
	&game->img_width, &game->img_height);
	game->img_item[8] = mlx_xpm_file_to_image(game->mlx, ITEM9, \
	&game->img_width, &game->img_height);
	game->img_item[9] = mlx_xpm_file_to_image(game->mlx, ITEM10, \
	&game->img_width, &game->img_height);
	load_image_item_2(game);
}
