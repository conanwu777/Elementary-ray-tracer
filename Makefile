NAME = rtv1
CC = gcc
CFLAGS = -O3 -Wall -Wextra -Werror
SRC = main.c utility.c read.c read_cont.c intersect.c light.c vector.c rot.c
OBJ = $(SRC:.c=.o)

GRAPHICS = -framework OpenGL -framework AppKit -lpthread
MLX_LNK = -L ./minilibx_macos -lmlx
FT_LNK = -L ./libft -lft

all:
	$(CC) $(CFLAGS) $(MLX_LNK) $(FT_LNK) $(GRAPHICS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
