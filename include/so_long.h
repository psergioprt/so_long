#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "../util_funcs/ft_printf/ft_printf.h"
# include "../util_funcs/Libft/libft.h"
# include "../util_funcs/get_next_line/get_next_line.h"

void	add_print_lines(char ***map, int fd);
void	mem_free(char ***map, int line_count);
int	map_mem_allocate(char ***map, int fd, int line_ct, int max_line_lth); 

#endif
