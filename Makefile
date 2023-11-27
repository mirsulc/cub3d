NAME	=	cub3D
CC	=	gcc
FLAGS	=	-Wall -Werror -Wextra # -g -fsanitize=address

SRC	=	src/main.c \
		src/map_control.c \
		src/map_control_2.c \
		src/map_control_3.c \
		src/map_parsing.c \
		src/cleaning.c \
		src/game.c \
		src/colors.c \
		src/moves.c \
		src/moves_2.c \
		src/raycasting.c \
		src/raycasting_2.c \
		src/utils.c \
		

LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)
MLX_PATH	= MLX42/
MLX_NAME	= build/libmlx42.a
MLX		= $(MLX_PATH)$(MLX_NAME)

H_FILE	= include/cub3d.h
RM	= rm -f

OBJ =		$(SRC:.c=.o)

MLX_FLAGS = -Iinclude -ldl -g -lglfw -pthread -lm


all: $(LIBFT) $(NAME) 

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(OBJ) 
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX)  $(MLX_FLAGS)

clean:
	@$(RM) $(OBJ)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	$(RM) $(NAME)
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: clean all

.PHONY: all clean fclean re
