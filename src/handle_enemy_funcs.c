/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_enemy_funcs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:45:10 by pauldos-          #+#    #+#             */
/*   Updated: 2024/07/31 18:47:33 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include <time.h>

void	check_map_dimensions_enemies(t_game *game)
{
	int	min_rows;
	int	min_columns;

	min_rows = 5;
	min_columns = 10;
	if (!game->map)
	{
		ft_printf("Error\nMap is NULL\n");
		mem_free(&game->map, game->line_count, game);
		exit(1);
	}
	if (game->line_count < min_rows || game->max_line_length < min_columns)
	{
		ft_printf("Error\nMap dimensions are too small for enemies\n");
		mem_free(&game->map, game->line_count, game);
		exit(1);
	}
}

void	init_handle_enemy_vars(t_game *game)
{
	int	i;

	i = 0;
	check_map_dimensions_enemies(game);
	game->num_enemies = 3;
	game->enemies = malloc(sizeof(t_enemy) * game->num_enemies);
	if (!game->enemies)
	{
		ft_printf("Error\nMemory allocation for enemies failed\n");
		mem_free(&game->map, game->line_count, game);
		exit(1);
	}
	while (i < game->num_enemies)
	{
		game->enemies[i].start_x = 1 + (rand() % (game->max_line_length - 2));
		game->enemies[i].start_y = 1 + (rand() % (game->line_count - 2));
		game->enemies[i].enemy_x = game->enemies[i].start_x;
		game->enemies[i].enemy_y = game->enemies[i].start_y;
		game->enemies[i].speed = 1;
		game->enemies[i].direction = rand() % 4;
		i++;
	}
	game->lives = 100;
}

void	check_enemy_moves_direction_boundaries(t_game *game, int i)
{
	t_enemy	*enemy;
	int		enemy_y;
	int		enemy_x;
	int		speed;
	char	**map;

	enemy = &game->enemies[i];
	enemy_y = enemy->enemy_y;
	enemy_x = enemy->enemy_x;
	speed = enemy->speed;
	map = game->map;
	if (rand() % 10 == 0 || map[enemy_y - speed][enemy_x] == '1' || \
		map[enemy_y][enemy_x - speed] == '1' || map[enemy_y + speed][enemy_x] \
		== '1' || map[enemy_y][enemy_x + speed] == '1')
		enemy->direction = rand() % 4;
	if (enemy->direction == 0 && map[enemy_y - speed][enemy_x] != '1')
		enemy_y -= speed;
	if (enemy->direction == 1 && map[enemy_y + speed][enemy_x] != '1')
		enemy_y += speed;
	if (enemy->direction == 2 && map[enemy_y][enemy_x - speed] != '1')
		enemy_x -= speed;
	if (enemy->direction == 3 && map[enemy_y][enemy_x + speed] != '1')
		enemy_x += speed;
	enemy->enemy_x = enemy_x;
	enemy->enemy_y = enemy_y;
}

void	move_enemies(t_game *game)
{
	static clock_t	last_move_time = 0;
	clock_t			current_time;
	double			elapsed_time;
	const double	move_interval = 0.5;
	int				i;

	i = 0;
	current_time = clock();
	elapsed_time = (double)(current_time - last_move_time) / CLOCKS_PER_SEC;
	if (elapsed_time < move_interval)
		return ;
	last_move_time = current_time;
	while (i < game->num_enemies)
	{
		check_enemy_moves_direction_boundaries(game, i);
		i++;
	}
	check_player_lives(game);
}

void	check_player_lives(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_enemies)
	{
		if (game->player_x == game->enemies[i].enemy_x && \
			game->player_y == game->enemies[i].enemy_y)
		{
			game->lives -= 25;
			ft_printf("You lost a life, you have %d lives left\n", game->lives);
			if (game->lives <= 0)
			{
				ft_printf("You have run out of lives. Game Over\n");
				mem_free(&game->map, game->line_count, game);
				cleanup_mlx(game);
				exit(0);
			}
			return ;
		}
		i++;
	}
}
