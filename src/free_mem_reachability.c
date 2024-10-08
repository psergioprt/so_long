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
		}
		exit(1);
	}
}

void	check_map_not_null(t_game *game)
{
	int	min_rows;
	int	min_columns;

	min_rows = 4;
	min_columns = 4;
	if (!game->map)
	{
		ft_printf("Error\nMap is NULL\n");
		mem_free(&game->map, game->line_count);
		exit(1);
	}
	if (game->line_count < min_rows || game->max_line_length < min_columns)
	{
		ft_printf("Error\nEither map is empty ");
		ft_printf("or dimensions are too small!\n");
		mem_free(&game->map, game->line_count);
		exit(1);
	}
}
