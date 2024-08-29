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

#include "../include_bonus/so_long_bonus.h"

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
				ft_printf("Error\n%c element is not reachable at POS row:%d "
					"column:%d\n", game->map[i][j], i + 1, j + 1);
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

static void	init_visited(t_flood_fill_vars *f)
{
	int	i;
	int	j;

	i = 0;
	f->visited = malloc(f->rows * sizeof(int *));
	if (f->visited == NULL)
	{
		ft_printf("Error:\nMemory allocation failed for visited array\n");
		exit(1);
	}
	while (i < f->rows)
	{
		f->visited[i] = malloc(f->cols * sizeof(int));
		if (f->visited[i] == NULL)
		{
			ft_printf("Error:\nMemory allocation failed for "
				"visited row %d\n", i);
			exit(1);
		}
		j = 0;
		while (j < f->cols)
			f->visited[i][j++] = 0;
		i++;
	}
}

void	check_player_trapped(t_flood_fill_vars *f, t_game *game)
{
	int	player_trapped;
	int	i;
	int	j;
	int	flag;

	player_trapped = 1;
	i = 0;
	while (i < f->rows)
	{
		j = 0;
		while (j < f->cols)
		{
			if ((f->map[i][j] == 'C' || f->map[i][j] == 'E') && \
				f->visited[i][j] == 1)
				player_trapped = 0;
			j++;
		}
		i++;
	}
	if (player_trapped)
	{
		ft_printf("Error: Player 'P' is surrounded by walls or trapped\n");
		flag = 1;
		free_flood_mem(game, f, &flag);
	}
}

void	validate_reachability(t_game *game)
{
	t_flood_fill_vars	f;
	int					flag;

	flag = 0;
	f.rows = game->line_count;
	f.cols = game->max_line_length;
	f.map = game->map;
	init_visited(&f);
	define_player_position(game, &f);
	flood_fill(&f, game->player_x, game->player_y);
	check_player_trapped(&f, game);
	check_c_e_reachability(game, &f);
	free_flood_mem(game, &f, &flag);
}
