/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:18:43 by pauldos-          #+#    #+#             */
/*   Updated: 2023/11/29 11:18:49 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen_gnl(const char *string)
{
	size_t	count;

	count = 0;
	if (!string)
		return (0);
	while (string[count])
		count++;
	return (count);
}

char	*ft_strchr_gnl(const char *str, int c)
{
	unsigned int	i;

	i = 0;
	if (!str)
		return (0);
	if (c == '\0')
		return ((char *)&str[ft_strlen_gnl(str)]);
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char				*newstr;
	int					i;
	int					j;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	newstr = malloc(sizeof(char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (newstr == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			newstr[i] = s1[i];
	while (s2[j] != '\0')
		newstr[i++] = s2[j++];
	newstr[ft_strlen_gnl(s1) + ft_strlen_gnl(s2)] = '\0';
	free(s1);
	return (newstr);
}

char	*ft_get_line(char *str)
{
	int		i;
	char	*newstring;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	newstring = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		newstring[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		newstring[i] = str[i];
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}

char	*ft_update_static_str(char *static_str)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	while (static_str[i] && static_str[i] != '\n')
		i++;
	if (!static_str[i])
	{
		free(static_str);
		return (NULL);
	}
	newstr = (char *)malloc(sizeof(char) * (ft_strlen_gnl(static_str) - i + 1));
	if (!newstr)
		return (NULL);
	i++;
	j = 0;
	while (static_str[i])
		newstr[j++] = static_str[i++];
	newstr[j] = '\0';
	free(static_str);
	return (newstr);
}
