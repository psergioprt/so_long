#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct map_area
{
	int	rows;
	int	columns;
	int	coins;
	int	exit;
	int	players;
}	t_map;

int	ft_atoi(char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	if (*str >= 9 && *str <= 13 || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		res = res * 10 + *str++ - '0';
	return (res * sign);
}

void	print_number(int n)
{
	char	buffer[12];
	int	len = 0;
	int	is_negative = 0;
	int	temp = n;

	if (n == 0)
	{
		char	zero = '0';
		write (1, &zero, 1);
		return ;
	}
	if (n < 0)
	{
		is_negative = 1;
		n = -n;
	}

	while (temp != 0)
	{
		len++;
		temp = temp / 10;
	}
	buffer[len + is_negative] = '\0';
	while (n > 0)
	{
		buffer[--len + is_negative] = (n % 10) + '0';
		n = n / 10;
	}
	if (is_negative)
	{
		buffer[0] = '-';
	}
	write (1, buffer, strlen(buffer));
}

void	print_numbers(int n)
{
	if (n < 10 && n >= 0)
	{
		char digit = n + '0';
		write (1, &digit, 1);
	}
	else
	{
		print_number(n);
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		write(STDERR_FILENO, "Error: Arguments number are not 2\n", 34);
		return (EXIT_FAILURE);
	}

	int	i = ft_atoi(argv[1]);
	while (i < 114)
	{
		print_numbers(i);
		write(1, " -> Hello world\n", 16);
		i++;
	}
	return (0);
}
