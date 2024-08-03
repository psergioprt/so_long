/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reachability.c                               :+:      :+:    :+:   */
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

static void	init_visited(t_flood_fill_vars *f)
{
	int	i;
	int	j;

	i = 0;
	f->visited = malloc(f->rows * sizeof(int *));
	while (i < f->rows)
	{
		f->visited[i] = malloc(f->cols * sizeof(int));
		j = 0;
		while (j < f->cols)
		{
			f->visited[i][j] = 0;
			j++;
		}
		i++;
	}
}

static void	define_player_position(t_game *game, t_flood_fill_vars *f)
{
	int	i;
	int	j;

	i = 0;
	while (i < f->rows)
	{
		j = 0;
		while (j < f->cols)
		{
			if (game->map[i][j] == 'P')
			{
				game->player_x = j;
				game->player_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

static void	check_c_e_reachability(t_game *game, t_flood_fill_vars *f)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (i < f->rows)
	{
		j = 0;
		while (j < f->cols)
		{
			if ((game->map[i][j] == 'C' || game->map[i][j] == 'E') && \
					(!f->visited[i][j]))
			{
				ft_printf("Error\n%c element is not reachable", \
						game->map[i][j]);
				flag = 1;
				free_flood_mem(game, f, &flag);
			}
			j++;
		}
		i++;
	}
	flag = 0;
	free_flood_mem(game, f, &flag);
}

void	validate_reachability(t_game *game)
{
	t_flood_fill_vars	f;
	int					flag;

	f.rows = game->line_count;
	f.cols = game->max_line_length;
	f.map = game->map;
	init_visited(&f);
	define_player_position(game, &f);
	flood_fill(&f, game->player_x, game->player_y);
	if (f.visited[game->player_x][game->player_y] == 0)
	{
		ft_printf("Error\nPlayer 'P' is surrounded by walls\n");
		flag = 1;
		free_flood_mem(game, &f, &flag);
	}
	check_c_e_reachability(game, &f);
}
