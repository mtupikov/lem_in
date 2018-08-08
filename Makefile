NAME = lem_in

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./inc/
LIB_DIR = ./libft/

SRC = 	main.c \
		reader.c \
		room_utils.c \
		go_ants.c \
		go_ants_utils_1.c \
		go_ants_utils_2.c \
		go_ants_utils_3.c \
		go_ants_utils_4.c \
		utils_of_room_utils.c \
		sh_paths.c \

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

LIBFT = $(LIB_DIR)libft.a
LIBFT_INC = $(LIB_DIR)includes/
LIBFT_FLAGS = -lft -L $(LIB_DIR)

CC_FLAGS = -Wall -Wextra -Werror
CC = gcc

HEADER_FLAGS = -I $(INC_DIR) -I $(LIBFT_INC)

all: vis $(NAME)

$(NAME) : $(LIBFT) $(OBJ) #vis
	@$(CC) $(OBJ) $(LIBFT_FLAGS) -o $(NAME)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@$(CC) -c $< -o $@ $(CC_FLAGS) $(HEADER_FLAGS)

vis:
	@make -C ./visualisation

$(LIBFT):
	@make -C $(LIB_DIR)

clean:
	@rm -f $(OBJ)
	@make clean -C $(LIB_DIR)
	@make clean -C ./visualisation

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@make fclean -C $(LIB_DIR)
	@make fclean -C ./visualisation

re: fclean all

.PHONY: all clean fclean re
