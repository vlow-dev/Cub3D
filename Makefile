NAME = cub3d

SRC_DIR = src
INC_DIR = include
LIBFT_DIR = libft

## MLX
MLX_DIR = minilibx-linux
LIB_MLX = $(MLX_DIR)/libmlx_Linux.a
1X_FLAGS = -lXext -lX11 -lm -lz

SRC = $(wildcard $(SRC_DIR)/*.c)

OBJ = $(SRC:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o)
TEST = src/parsing.c

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
IFLAGS = -I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR) -I$(MLX_DIR)
LFLAGS = -l$(LIBFT_DIR)/libft.a
LIBFT = $(LIBFT_DIR)/libft.a
AR = ar
ARFLAGS = rcs

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(LIB_MLX)
	@echo "Creating $(NAME)..."
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJ) $(LIBFT) $(LIB_MLX) $(1X_FLAGS) -o $(NAME) 
	@echo "Created $(NAME)"

$(LIBFT):
	@make -C $(LIBFT_DIR) all

$(LIB_MLX):
	@make -C $(MLX_DIR) all

bonus: all

test:  $(LIBFT)
	@echo "Creating $(NAME)..."
	@$(CC) $(CFLAGS) $(IFLAGS) $(TEST) $(LIBFT) 
	@echo "Created $(NAME)"

%.o: %.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@echo "Removing objects files..."
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@rm -f $(OBJ)
	@echo "Objects files removed."

fclean: clean
	@echo "Removing $(NAME)..."
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(NAME) removed."

re: fclean all

debug: CFLAGS += -g3 -fpic
debug: clean all
	@make -C $(LIBFT_DIR) debug
	@echo "Enable debug mode"

valgrind:
	valgrind --leak-check=full ./cub3d

fval:
	valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3d

fsanitize: CFLAGS += -fsanitize=address,leak -g3 -O1
fsanitize: clean all
	@echo "AddressSanitizer enabled for $(NAME)"

fsan: fsanitize

.PHONY: all clean fclean re bonus debug valgrind fsanitize fsan fval test
