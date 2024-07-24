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
#define MAP_FILE "map.ber"

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

int	main(int argc, char *argv[])
{
	int		fd;
	int		line_count;
	int		max_line_length;
	char	**map;

	if (argc != 2)
		return (1);
	line_count = 0;
	max_line_length = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	map_read(fd, &line_count, &max_line_length);
	lseek(fd, 0, SEEK_SET);
	if (map_mem_allocate(&map, fd, line_count, max_line_length) != 0)
		return (1);
	add_print_lines(&map, fd);
	mem_free(&map, line_count);
	return (0);
}
