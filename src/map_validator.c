/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:23:23 by pauldos-          #+#    #+#             */
/*   Updated: 2024/07/26 08:29:00 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

bool	check_rectangle(char **map, int line_count)
{
	int	line_length;
	int	i;

	i = 1;
	line_length = ft_strlen(map[0]);
	while (i < line_count)
	{
		if (ft_strlen(map[i]) != line_length)
			return (false);
		i++;
	}
	return (true);
}

bool	check_full_fill(char **map, int line_count)
{
	int	line_length;
	int	i;
	int	j;

	i = 0;
	while (i < line_count)
	{
		line_length = ft_strlen(map[i]) - 1;
		j = 0;
		while (j < line_length)
		{
			if (map[i][j] != 'P' && map[i][j] != 'E' && map[i][j] != '0' \
					&& map[i][j] != 'C' && map[i][j] != '1')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_map_elements(char **map, int line_count)
{
	int		i;
	int		j;
	int		row_len;
	t_game	items;

	i = 0;
	init_game(&items);
	while (i < line_count)
	{
		row_len = ft_strlen(map[i]) - 1;
		j = 0;
		while (j < row_len)
		{
			if (map[i][j] == 'P')
				items.player++;
			if (map[i][j] == 'C')
				items.consumable++;
			if (map[i][j++] == 'E')
				items.exit_map++;
		}
		i++;
	}
	if (items.player != 1 || items.consumable < 1 || items.exit_map != 1)
		return (false);
	return (true);
}

bool	check_wall(char **map, int line_count)
{
	int	i;
	int	j;
	int	line_length;

	i = 0;
	while (i < line_count)
	{
		line_length = ft_strlen(map[i]) - 1;
		j = 0;
		while (j < line_length)
		{
			if (i == 0 && map[i][j] != '1')
				return (false);
			if ((i > 0 && i < (line_count - 1) && (j == 0 || \
							j == line_length - 1) && map[i][j] != '1'))
				return (false);
			if ((i == line_count - 1) && map[i][j] != '1')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	validate_map(char **map, int line_count)
{
	if (!(check_rectangle(map, line_count)))
	{
		ft_printf("Map is not rectangular\n");
		return (false);
	}
	if (!(check_full_fill(map, line_count)))
	{
		ft_printf("Map isn't filled with only the allowed characters\n");
		return (false);
	}
	if (!(check_map_elements(map, line_count)))
	{
		ft_printf("Map hasn't the required element number\n");
		return (false);
	}
	if (!(check_wall(map, line_count)))
	{
		ft_printf("Wall is not correct\n");
		return (false);
	}
	ft_printf("Map is OK\n");
	return (true);
}
