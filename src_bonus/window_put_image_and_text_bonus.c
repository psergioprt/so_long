/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_put_image_and_text.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:26:34 by pauldos-          #+#    #+#             */
/*   Updated: 2024/08/04 14:34:18 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/so_long_bonus.h"

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
	t_draw_shape	rectangle;
	char			*move_str;
	int				text_color;
	int				x;
	int				y;

	move_str = ft_itoa(game->move_count);
	if (!move_str)
	{
		ft_printf("Error\nFailed to allocate memory for rectangle string\n");
		return ;
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

void	display_items_collected(t_game *game)
{
	t_draw_shape	v;
	t_draw_shape	rectangle;
	int				x;
	int				y;

	v.item_str = ft_itoa(game->items_collected);
	v.f_item_str = ft_itoa(game->total_items);
	if (!v.item_str || !v.f_item_str)
	{
		ft_printf("Error\nFailed to allocate memory for rectangle string\n");
		return ;
	}
	v.t_colr = 0xFFFFFF;
	rectangle.color = 0x000000;
	x = 250;
	y = 20;
	rectangle.width = 140;
	rectangle.height = 20;
	draw_rectangle(game, rectangle, x - 5, y - 15);
	mlx_string_put(game->mlx, game->window, x, y, v.t_colr, "Collected: ");
	mlx_string_put(game->mlx, game->window, x + 70, y, v.t_colr, v.item_str);
	mlx_string_put(game->mlx, game->window, x + 80, y, v.t_colr, " / ");
	mlx_string_put(game->mlx, game->window, x + 100, y, v.t_colr, v.f_item_str);
	free(v.item_str);
	free(v.f_item_str);
}

void	display_player_lives(t_game *game)
{
	t_draw_shape	lives;
	t_draw_shape	rectangle;
	int				x;
	int				y;
	int				lcolor;

	lives.lives_str = ft_itoa(game->lives);
	if (!lives.lives_str)
	{
		ft_printf("Error\nFailed to allocate memory for rectangle string\n");
		return ;
	}
	lives.lives_color = 0xFFFFFF;
	lcolor = lives.lives_color;
	rectangle.color = 0x000000;
	x = 550;
	y = 20;
	rectangle.width = 80;
	rectangle.height = 20;
	draw_rectangle(game, rectangle, x - 5, y - 15);
	mlx_string_put(game->mlx, game->window, x, y, lcolor, "Energy: ");
	mlx_string_put(game->mlx, game->window, x + 50, y, lcolor, lives.lives_str);
	free(lives.lives_str);
}

int	loop_hook(t_game *game)
{
	mlx_clear_window(game->mlx, game->window);
	items_frame_loop(game);
	render_game(game);
	move_enemies(game);
	display_move_count(game);
	display_items_collected(game);
	display_player_lives(game);
	return (0);
}
