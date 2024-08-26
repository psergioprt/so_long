/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem_reachability_check_enemies_alloc.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:44:13 by pauldos-          #+#    #+#             */
/*   Updated: 2024/07/31 11:29:46 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_flood_mem(t_game *game, t_flood_fill_vars *f, int *flag)
{
	int	i;

	if (*flag == 1)
	{
		i = 0;
		while (i < f->rows)
			free(f->visited[i++]);
		free(f->visited);
		i = 0;
		while (i < f->rows)
			free(game->map[i++]);
		free(game->map);
		cleanup_enemy_array(game);
		exit(1);
	}
	else if (*flag == 0)
	{
		i = 0;
		while (i < f->rows)
			free(f->visited[i++]);
		free(f->visited);
	}
}

void	check_enemies_alloc(t_game *game)
{
	if (!game->enemies)
	{
		ft_printf("Error\nMemory allocation for enemies failed\n");
		mem_free(&game->map, game->line_count, game);
		exit (1);
	}
}
