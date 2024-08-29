/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_and_close_window.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 20:55:13 by pauldos-          #+#    #+#             */
/*   Updated: 2024/08/04 20:58:53 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/so_long_bonus.h"

int	window_esc_key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_window(game);
	return (0);
}

int	close_window(t_game *game)
{
	free_game_resources(game);
	exit(0);
	return (0);
}
