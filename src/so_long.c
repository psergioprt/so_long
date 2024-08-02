/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:23:23 by pauldos-          #+#    #+#             */
/*   Updated: 2024/07/24 09:25:00 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	map_read(int fd, int *line_count, int *max_line_length)
{
	char	*line;
	char	line_length;

	line = get_next_line(fd);
	while (line != NULL)
	{
		line_length = ft_strlen(line);
		if (line[line_length - 1] == '\n')
			line_length--;
		if (line_length > *max_line_length)
			*max_line_length = line_length;
		(*line_count)++;
		free(line);
		line = get_next_line(fd);
	}
}

void	init_game(t_game *game)
{
	game->line_count = 0;
	game->max_line_length = 0;
	game->map = NULL;
	game->player = 0;
	game->item = 0;
	game->exit_map = 0;
	game->mlx = NULL;
	game->window = NULL;
	game->img_player = NULL;
	game->img_wall = NULL;
	game->img_exit = NULL;
	game->img_road = NULL;
	game->img_item = NULL;
	game->img_width = 0;
	game->img_height = 0;
	game->should_exit = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->total_items = 0;
	game->items_collected = 0;
}

void	start_mlx_functions(t_game *game)
{
	init_mlx(game);
	load_image(game);
	mlx_loop_hook(game->mlx, loop_hook, game);
	mlx_key_hook(game->window, key_press, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char *argv[])
{
	int		fd;
	t_game	game;	

	if (argc != 2)
		return (1);
	init_game(&game);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	map_read(fd, &game.line_count, &game.max_line_length);

	lseek(fd, 0, SEEK_SET);
	if (map_mem_allocate(&game.map, fd, game.line_count, \
				game.max_line_length) != 0)
		return (1);
	add_print_lines(&game.map, fd);
	close (fd);
	if (!validate_map(game.map, game.line_count, &game)) //added &game
	{
		mem_free(&game.map, game.line_count);
		return (1);
	}
	printf("Main after validate_map, total items value is %d\n", game.total_items);
	validate_reachability(&game);
	start_mlx_functions(&game);
	return (0);
}
