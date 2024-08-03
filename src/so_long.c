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

void	start_mlx_functions(t_game *game)
{
	init_mlx(game);
	load_image(game);
	mlx_loop_hook(game->mlx, loop_hook, game);
	mlx_key_hook(game->window, key_press, game);
	mlx_hook(game->window, DESTROY_NOTIFY, 0, close_window, game);
	mlx_loop(game->mlx);
}

int	start_validations(t_game *game)
{
	if (!validate_map(game->map, game->line_count, game))
	{
		mem_free(&game->map, game->line_count);
		return (1);
	}
	validate_reachability(game);
	return (0);
}

int	start_map_mem_allocate(t_game *game, int fd)
{
	if (map_mem_allocate(&game->map, fd, game->line_count, \
				game->max_line_length) != 0)
	{
		ft_printf("Error\nFailed to allocate map memory!\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int		fd;
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error\nPlease use '%s maps/filename.ber'\n", argv[0]);
		return (1);
	}
	init_game_struct_variables(&game);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nThe file doesn't exist or wrong name!\n");
		return (1);
	}
	map_read(fd, &game.line_count, &game.max_line_length);
	close (fd);
	fd = open(argv[1], O_RDONLY);
	start_map_mem_allocate(&game, fd);
	add_print_lines(&game.map, fd);
	close (fd);
	if (start_validations(&game) != 0)
		return (1);
	start_mlx_functions(&game);
	return (0);
}
