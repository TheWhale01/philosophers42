CC=gcc
BIN_DIR=bin/
OBJ_DIR=obj/
SRC_DIR=src/
INCLUDES=includes/
CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES)
NAME=$(BIN_DIR)philo

CFILES=$(addprefix $(SRC_DIR), main.c)
OBJS=$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(CFILES))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@if [ ! -d "$(dir $@)" ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@if [ ! -d "./$(BIN_DIR)" ]; then mkdir $(dir $@); fi
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

debug: CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES) -g
debug: $(NAME)

clean:
	$(MAKE) clean -C $(MLX_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(BIN_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)

sanitize:CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES) -fsanitize=address
sanitize: $(NAME)

re: fclean all

re_debug: fclean debug

re_sanitize: fclean sanitize

.PHONY: all debug clean fclean sanitize re re_debug re_sanitize