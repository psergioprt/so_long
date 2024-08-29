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

#include "../include_bonus/so_long_bonus.h"

void	flood_fill(t_flood_fill_vars *vars, int x, int y)
{
	if (x < 0 || y < 0 || x >= vars->cols || y >= vars->rows || \
			vars->map[y][x] == '1' || vars->visited[y][x])
		return ;
	vars->visited[y][x] = 1;
	flood_fill(vars, x + 1, y);
	flood_fill(vars, x - 1, y);
	flood_fill(vars, x, y + 1);
	flood_fill(vars, x, y - 1);
}

void	free_flood_mem_2(t_flood_fill_vars *f, int *i)
{
	*i = 0;
	if (f->visited != NULL)
	{
		while (*i < f->rows)
		{
			if (f->visited[*i] != NULL)
			{
				free(f->visited[*i]);
				f->visited[*i] = NULL;
			}
			(*i)++;
		}
		free(f->visited);
		f->visited = NULL;
	}
}

void	free_flood_mem(t_game *game, t_flood_fill_vars *f, int *flag)
{
	int	i;

	free_flood_mem_2(f, &i);
	i = 0;
	if (*flag == 1)
	{
		if (game->map != NULL)
		{
			while (i < f->rows)
			{
				if (game->map[i] != NULL)
				{
					free(game->map[i]);
					game->map[i] = NULL;
				}
				i++;
			}
			free(game->map);
			game->map = NULL;
			cleanup_enemy_array(game);
		}
		exit(1);
	}
}

/*void	free_flood_mem(t_game *game, t_flood_fill_vars *f, int *flag)
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
}*/

void	check_enemies_alloc(t_game *game)
{
	if (!game->enemies)
	{
		ft_printf("Error\nMemory allocation for enemies failed\n");
		mem_free(&game->map, game->line_count, game);
		exit (1);
	}
}
