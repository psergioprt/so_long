#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../util_funcs/Libft/libft.h"

typedef struct map_area
{
	int	rows;
	int	columns;
	int	coins;
	int	exit;
	int	players;
}	t_map;

int	main(int argc, char *argv[])
{
	char	*name = argv[1];
	int	len = ft_strlen(name);

	if (argc != 2)
	{
		write(STDERR_FILENO, "Error: Arguments number are not 2\n", 34);
		return (EXIT_FAILURE);
	}
	ft_putstr(name);
	char len_char = len + '0';
	write(1, "\n", 1);
	write (1, &len_char, 1);
	return (0);
}
