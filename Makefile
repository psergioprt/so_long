# Variable definition
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -I$(INCDIR) -Iutil_funcs/Libft  -Iutil_funcs/ft_printf -Iutil_funcs/get_next_line

   # Include MLX and X11 header files. Look at the correct folder
   # whether the system is Linux or MacOS

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	INC_X11_MLX = -I/usr/include -Imlx
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
	MLX_LIB = libmlx_Linux.a
else
	INC_X11_MLX = -I/opt/X11/include -Imlx
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework Appkit
	MLX_LIB = libmlx.a
endif

NAME = so_long
SRCDIR = src
OBJDIR = obj
INCDIR = include
LIBFTDIR = util_funcs/Libft
PRINTF_DIR = util_funcs/ft_printf
GNLDIR = util_funcs/get_next_line
MLXDIR = ./mlx
MLXOBJDIR = $(MLXDIR)/obj

LIBFT = $(LIBFTDIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a
GNL = $(GNLDIR)/next_line.a
MLX = $(MLXDIR)/$(MLX_LIB)

# Holds linker flags for printf(-L adds ft_printf folder, (-l specifies the library to link)
LDFLAGS = -L$(LIBFTDIR) -lft -L$(PRINTF_DIR) -lftprintf -L$(GNLDIR) -l:next_line.a $(MLX_FLAGS)

# Define color codes
COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_YELLOW=\033[0;33m
COLOUR_RESET=\033[0m

.SILENT:

all: $(MLX) $(NAME)

# wildcard to find all sources files
SRC = 	$(wildcard $(SRCDIR)/*.c)

# defines object files corresponding to each source file
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

# Main target of the Makefile (push_swap), depends on Objs and Libft
# compiles the source files, links them to Libft and ft_printf Library
# and produces push_swap executable
$(NAME): $(OBJS) $(LIBFT) $(PRINTF) $(GNL) $(MLX)
	@echo "$(COLOUR_GREEN)=>Linking objects...$(COLOUR_RESET)"
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Generate object files from source files.
# Compiles each .c in the SRCDIR into corresponding .o file in OBJDIR
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(wildcard $(INCDIR)/*.h)
	@echo "$(COLOUR_BLUE)=>Compiling so_long...$(COLOUR_RESET)"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# To ensure GNL library is built by invoking make if GNLDIR
$(GNL):
	$(MAKE) -C $(GNLDIR)

# To ensure Libft library is built by invoking make in LIBFDIR
$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

# To ensure ft_printf library is built by invoking make in PRINTF_DIR
$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

# To ensure MLX library is built by invoking make in MLXDIR

$(MLX):
	$(MAKE) -C $(MLXDIR)

# Removes all object files, the push_swap executable and Libft library
# Rebuilds Libft library
clean:
	@echo "$(COLOUR_YELLOW)=> Cleaning So_long library...$(COLOUR_RESET)"
	@$(RM) -r $(OBJDIR)
	@echo "$(COLOUR_YELLOW)=> Cleaning Libft library...$(COLOUR_RESET)"
	@$(MAKE) -C $(LIBFTDIR) clean
	@echo "$(COLOUR_YELLOW)=> Cleaning ft_printf library...$(COLOUR_RESET)"
	@$(MAKE) -C $(PRINTF_DIR) clean
	@echo "$(COLOUR_YELLOW)=> Cleaning get_next_line library...$(COLOUR_RESET)"
	@$(MAKE) -C $(GNLDIR) clean
	@echo "$(COLOUR_YELLOW)=> Cleaning MLX library...$(COLOUR_RESET)"
	@$(MAKE) -C $(MLXDIR) clean
	@$(RM) -r $(MLXOBJDIR)



fclean:
	@echo "$(COLOUR_YELLOW)=> Cleaning So_long library...$(COLOUR_RESET)"
	@$(RM) -rf $(OBJDIR) $(NAME)
	@echo "$(COLOUR_YELLOW)=> Cleaning Libft library...$(COLOUR_RESET)"
	@$(MAKE) -C $(LIBFTDIR) fclean
	@echo "$(COLOUR_YELLOW)=> Cleaning ft_printf library...$(COLOUR_RESET)"
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@echo "$(COLOUR_YELLOW)=> Cleaning get_next_line library...$(COLOUR_RESET)"
	@$(MAKE) -C $(GNLDIR) fclean
	@echo "$(COLOUR_YELLOW)=> Cleaning MLX library...$(COLOUR_RESET)"
	@$(MAKE) -C $(MLXDIR) clean
	@$(RM) -r $(MLXOBJDIR)

re:	fclean all

# Clean is a phony target, which means it doesn't output a file
# with the same name "clean".
.PHONY: clean fclean deploy re all
deploy:

