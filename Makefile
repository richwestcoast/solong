CC = cc
#CFLAGS = -Wall -Wextra -Werror -g
CFLAGS = -g
MLXFLAGS = -L ./libs/minilibx-linux -lm -lmlx -Ilmlx -lXext -lX11 
DEPS = libs/minilibx-linux/mlx.h libs/libft/libft.a

NAME = so_long
NAME_BONUS = so_long_bonus

SRC = src/checks.c src/helpers.c src/so_long.c src/movements.c src/libx.c src/validation.c src/initializing.c
OBJ = $(SRC:.c=.o)

LIBFT = libs/libft/libft.a

all: libs $(NAME)

$(LIBFT):
	#$(MAKE) -C ./libs/libft

libs:
	#$(MAKE) -C ./libs/minilibx-linux
	
$(NAME): $(OBJ) $(libs) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)



clean:
	#$(MAKE) $@ -C ./libs/libft
	#$(MAKE) $@ -C ./libs/minilibx-linux
	@rm -rf $(OBJ)

fclean: clean
	$(MAKE) $@ -C ./libs/libft
	@rm -rf $(NAME)

re: fclean all
	#$(MAKE) re -C ./libs/libft
	#$(MAKE) re -C ./libs/minilibx-linux
