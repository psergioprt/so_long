/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:47:23 by pauldos-          #+#    #+#             */
/*   Updated: 2024/07/24 11:47:56 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_game_struct_variables(t_game *game)
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
	game->move_count = 0;
}

void	add_print_lines(char ***map, int fd)
{
	int		row;
	int		i;
	char	*line;

	row = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_strcpy((*map)[row], line);
		free(line);
		line = get_next_line(fd);
		row++;
	}
	close(fd);
	i = 0;
	while (i < row)
	{
		ft_printf("%s\n", (*map)[i]);
		i++;
	}
}

void	mem_free(char ***map, int line_count)
{
	int	i;

	i = 0;
	while (i < line_count)
		free((*map)[i++]);
	free(*map);
}

int	map_mem_allocate(char ***map, int fd, int line_count, int max_line_length)
{
	int	i;
	int	j;

	*map = malloc(sizeof(char *) * line_count);
	if (!(*map))
	{
		close (fd);
		return (1);
	}
	i = 0;
	while (i < line_count)
	{
		(*map)[i] = malloc(sizeof(char) * (max_line_length + 2));
		if (!((*map)[i]))
		{
			j = 0;
			while (j++ < i)
				free((*map)[j]);
			free(*map);
			close (fd);
			return (1);
		}
		(*map)[i++][max_line_length] = '\0';
	}
	return (0);
}
