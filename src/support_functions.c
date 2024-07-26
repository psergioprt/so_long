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

int	map_mem_allocate(char ***map, int fd, int line_ct, int max_line_lth)
{
	int	i;
	int	j;

	*map = malloc(sizeof(char *) * line_ct);
	if (!(*map))
	{
		close (fd);
		return (1);
	}
	i = 0;
	while (i < line_ct)
	{
		(*map)[i] = malloc(sizeof(char) * (max_line_lth + 1));
		if (!((*map)[i]))
		{
			j = 0;
			while (j++ < i)
				free((*map)[j]);
			free(*map);
			close (fd);
			return (1);
		}
		i++;
	}
	return (0);
}
