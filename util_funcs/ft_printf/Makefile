NAME = libftprintf.a

AR	= ar crs

CC	= cc
CCFLAGS = -Wall -Wextra -Werror
RM	= rm -rf

# Define color codes
COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_YELLOW=\033[0;33m
COLOUR_RESET=\033[0m

.SILENT:

SRC	= ft_printf.c \
	  ft_printf_strlen.c \
	  ft_printf_putchar.c \
	  ft_printf_putstr.c \
	  ft_print_int.c \
	  ft_print_int_u.c \
	  ft_print_hex.c \
	  ft_printf_strchr.c \
	  ft_print_ptr.c

OBJ	= $(SRC:%.c=%.o)

$(NAME): $(OBJ)
	@echo "$(COLOUR_GREEN)=>Linking objects...$(COLOUR_RESET)"
	$(AR) $(NAME) $(OBJ)

all: $(NAME)

clean:
	@echo "$(COLOUR_YELLOW)=> Cleaning ft_printf library...$(COLOUR_RESET)"
	$(RM) $(OBJ)

fclean: clean
	@echo "$(COLOUR_YELLOW)=> Cleaning ft_printf library...$(COLOUR_RESET)"
	$(RM) $(NAME)

re: fclean all
