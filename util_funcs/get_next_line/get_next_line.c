/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:17:15 by pauldos-          #+#    #+#             */
/*   Updated: 2023/11/29 11:55:23 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*ft_fill_static_str(int fd, char *static_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	rd_bytes = 1;
	while (!ft_strchr(static_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			free(static_str);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		static_str = ft_strjoin(static_str, buff);
	}
	free(buff);
	return (static_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*static_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_str = ft_fill_static_str(fd, static_str);
	if (!static_str)
		return (NULL);
	line = ft_get_line(static_str);
	static_str = ft_update_static_str(static_str);
	return (line);
}
/*
int	main(void)
{
	char	*str;
	char	*file;
	int		i;
	int		fd;

	file = "test.txt";
	fd = open(file, O_RDONLY);
	i = 0;
	while (i < 10)
	{
		str = get_next_line(fd);
		if (!str)
			break;
		printf("i: %i\n", i);
		printf("fd: %i %s", fd, str);
		free(str);
		i++;
	}
	close(fd);
	return (0); 
}*/
