/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:18:06 by pauldos-          #+#    #+#             */
/*   Updated: 2023/11/29 11:18:13 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>

char	*ft_fill_static_str(int fd, char *static_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
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
	static char	*static_str[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	static_str[fd] = ft_fill_static_str(fd, static_str[fd]);
	if (!static_str[fd])
		return (NULL);
	line = ft_get_line(static_str[fd]);
	static_str[fd] = ft_update_static_str(static_str[fd]);
	return (line);
}

/*int main()
{
	int fd = open("read_error.txt", O_RDONLY);
    int result;
    result = 0;
    while(result != 4)
    {
	    printf("%s",get_next_line(fd));
        result++;
    }
}*/
