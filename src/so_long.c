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
	int		line_length;

	line = get_next_line(fd);
	while (line != NULL)
	{
		(*line_count)++;
		line_length = ft_strlen(line);
		if (line_length > *max_line_length)
			*max_line_length = line_length;
		free (line);
		line = get_next_line(fd);
	}
}

void	init_game(t_game *game)
{
	game->line_count = 0;
	game->max_line_length = 0;
	game->map = NULL;
	game->player = 0;
	game->consumable = 0;
	game->exit_map = 0;
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
	validate_map(game.map, game.line_count);
	mem_free(&game.map, game.line_count);
	return (0);
}
