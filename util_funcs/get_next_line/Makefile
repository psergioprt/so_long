NAME = next_line.a
CC	= cc
CFFLAGS	= -Wall -Wextra -Werror
AR	= ar
ARFLAGS	= -rcs
RM	= rm
RMFLAGS	= -f

SRC	= get_next_line.c get_next_line_utils.c
OBJ	= $(SRC:.c=.o)

BONUS	= get_next_line_bonus.c get_next_line_utils_bonus.c
OBJ_BONUS = $(BONUS:.c=.o)

all: $(NAME) $(EXEC)

# Define color codes
COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_RESET=\033[0m

.SILENT:


$(NAME): $(OBJ)
	@echo "$(COLOUR_GREEN)=>Linking objects...$(COLOUR_RESET)"
	$(AR) $(ARFLAGS) $@ $(OBJ)

$(EXEC): $(NAME)
	$(CC) $(CFLAGS) -o $@ $(NAME)

bonus: $(OBJ) $(OBJ_BONUS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ) $(OBJ_BONUS)

%.o: %.c
	@echo "$(COLOUR_BLUE)=>Compiling Push_swap...$(COLOUR_RESET)"
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@echo "Cleaning get_next_line objects..."
	@$(RM) $(RMFLAGS) $(OBJ) $(OBJ_BONUS)

fclean: clean
	@echo "Cleaning get_next_line library..."
	@$(RM) $(RMFLAGS) $(NAME) $(EXEC)

re: fclean all

.PHONY: all clean fclean re bonus
