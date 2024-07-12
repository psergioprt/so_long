# Variable definition
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -I$(INCDIR) -Iutil_funcs/Libft  -Iutil_funcs/ft_printf -Iutil_funcs/get_next_line
NAME = so_long
SRCDIR = src
OBJDIR = obj
INCDIR = include
LIBFTDIR = util_funcs/Libft
PRINTF_DIR = util_funcs/ft_printf
GNLDIR = util_funcs/get_next_line

LIBFT = $(LIBFTDIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a
GNL = $(GNLDIR)/next_line.a

# Holds linker flags for printf(-L adds ft_printf folder, (-l specifies the library to link)
LDFLAGS = -L$(LIBFTDIR) -lft -L$(PRINTF_DIR) -lftprintf -L$(GNLDIR) -l:next_line.a

# Define color codes
COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_YELLOW=\033[0;33m
COLOUR_RESET=\033[0m

.SILENT:

all:$(NAME)

# wildcard to find all sources files
SRC = 	$(wildcard $(SRCDIR)/*.c)

# defines object files corresponding to each source file
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

# Main target of the Makefile (push_swap), depends on Objs and Libft
# compiles the source files, links them to Libft and ft_printf Library
# and produces push_swap executable
$(NAME): $(OBJS) $(LIBFT) $(PRINTF) $(GNL)
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

# To ensure ft_printf library is built by invoking make in PRINTF_FDIR
$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

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

fclean:
	@echo "$(COLOUR_YELLOW)=> Cleaning So_long library...$(COLOUR_RESET)"
	@$(RM) -rf $(OBJDIR) $(NAME)
	@echo "$(COLOUR_YELLOW)=> Cleaning Libft library...$(COLOUR_RESET)"
	@$(MAKE) -C $(LIBFTDIR) fclean
	@echo "$(COLOUR_YELLOW)=> Cleaning ft_printf library...$(COLOUR_RESET)"
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@echo "$(COLOUR_YELLOW)=> Cleaning get_next_line library...$(COLOUR_RESET)"
	@$(MAKE) -C $(GNLDIR) fclean

re:	fclean all

# Clean is a phony target, which means it doesn't output a file
# with the same name "clean".
.PHONY: clean fclean deploy re all
deploy:

