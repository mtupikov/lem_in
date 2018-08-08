NAME = visualiser

SRCDIR	= ./src/
INCDIR	= ./inc/
OBJDIR	= ./obj/

SRC =	main.c \
		hook_keydown.c \
		image.c \
		mlx_stuff.c \
		reader_v.c \
		render.c \
		room_utils.c \
		utils_of_room_utils.c \
		get_paths.c \
		vis_utils_1.c \
		vis_utils_2.c \
        vis_utils_3.c \

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g

MLX		= ./miniLibX/
MLX_LIB	= $(addprefix $(MLX),mlx.a)
MLX_INC	= -I ./miniLibX
MLX_LNK	= -L ./miniLibX -l mlx -framework OpenGL -framework AppKit

LIBFT		= ../libft/
LIBFT_LIB	= $(addprefix $(LIBFT),libft.a)
LIBFT_INC	= -I ../libft/includes
LIBFT_LNK	= -L ../libft -l ft

all: obj $(LIBFT_LIB) $(MLX_LIB) $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	@$(CC) $(CFLAGS) $(MLX_INC) $(LIBFT_INC) -I $(INCDIR) -o $@ -c $<

$(LIBFT_LIB):
	@make -C $(LIBFT)

$(MLX_LIB):
	@make -C $(MLX)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(MLX_LNK) $(LIBFT_LNK) -lm -o $(NAME)

clean:
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBFT)
	@make clean -C $(MLX)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
