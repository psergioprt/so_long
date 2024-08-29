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

#include "../include/so_long.h"

int	loop_hook(t_game *game)
{
	mlx_clear_window(game->mlx, game->window);
	render_game(game);
	return (0);
}
