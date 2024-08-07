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

void	map_read(int fd, int *line_count, int *max_line_length)
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

void	cleanup_enemy_array(t_game *game)
{
	if (game->enemies)
	{
		free(game->enemies);
		game->enemies = NULL;
	}
}

void	mem_free(char ***map, int line_count, t_game *game)
{
	int	i;

	i = 0;
	while (i < line_count)
		free((*map)[i++]);
	free(*map);
	cleanup_enemy_array(game);
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
