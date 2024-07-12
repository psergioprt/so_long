#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct so_long_struct
{
	int	count;
	int	max;
	int	min;
	char	*name;

} SO_LONG;

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);

}

int	sum (int a, int b)
{
	int	result;

	result = a + b;
	return (result);
}

int main (int argc, char *argv[])
{
	char	*name;
	int	len;
	int	len1;
	int	num1;
	int	num2;
	int	sum_digits;
	SO_LONG my_struct;
	my_struct.count = 10;
	my_struct.max = 5;
	my_struct.min = 0;
	my_struct.name = "Xico";
	SO_LONG *new_struct = NULL;

	if (argc == 3)
	{
		new_struct = (SO_LONG *)malloc(sizeof(SO_LONG));
		if (new_struct == NULL)
		{
			write (STDERR_FILENO, "Memory Allocation Error", 23);
			return (1);
		}
		new_struct->count = 50;
		new_struct->max = 100;
		new_struct->min = 90;
		new_struct->name = "Ambrosio";
	
		name = "Paulo Sergio";

		len1 = ft_strlen(name);
		len = ft_strlen(argv[0]);
		num1 = atoi(argv[1]);
		num2 = atoi(argv[2]);
		sum_digits = sum(num1, num2);
		printf("\nsize of argc[0] = %d\n", len);
		printf("\nsize of len1 = %d\n", len1);
		printf("%d\n", sum_digits);
		while (my_struct.min < my_struct.max)
		{
			printf("%s, %d\n", my_struct.name, my_struct.count);
			my_struct.min++;
			my_struct.count++;
		}
		while (new_struct->min < new_struct->max)
		{
			printf("%s, %d\n", new_struct->name, new_struct->count);
			new_struct->min++;
			new_struct->count++;
		}
	}
	else
	{
		write(2, "Please use ", 11);
		write (2, argv[0], ft_strlen(argv[0]));
		write (2, " definition\n", 12);
		return (1);
	}
	if (new_struct != NULL)
		free(new_struct);
	return (0);
}

