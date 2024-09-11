# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/15 16:43:25 by juramos           #+#    #+#              #
#    Updated: 2024/09/11 10:12:17 by juramos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name
NAME 		= 	cub3d

# Compiler
CC 			= 	gcc
CFLAGS 		= 	-Wall -Werror -Wextra -g3 # -fsanitize=address

# Sources
SRC_DIR 	= 	src/
SRC_FILES 	= 	main init_player utils parse raycasting
				
SRC 		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

# Objects
OBJ_DIR 	= 	obj/
OBJ_DIRS	=	$(sort $(dir $(OBJ)))
OBJ 		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

# libft
LIBFT_PATH	= 	libft/
LIBFT_NAME	= 	libft.a
LIBFT		= 	$(LIBFT_PATH)$(LIBFT_NAME)

# Mlx
MLX_PATH	= 	minilibx-linux/
MLX_NAME	= 	libmlx.a
MLX			= 	$(MLX_PATH)$(MLX_NAME)

# build path
# B_PATH = build/

# Includes
INC_MS		= -I includes/ \
			-I ./minilibx-linux

# Colors
DEF_COLOR 	= 	\033[0;39m
GRAY 		= 	\033[0;90m
RED 		= 	\033[0;91m
GREEN 		=	\033[0;92m
YELLOW 		=	\033[0;93m
BLUE 		=	\033[0;94m
MAGENTA 	=	\033[0;95m
CYAN 		= 	\033[0;96m
WHITE 		= 	\033[0;97m

# Config
OBJF 		=	.cache_exists
MAKEFLAGS 	+=	--no-print-directory
.SILENT:

###

all: $(MLX) $(LIBFT) $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
	@echo "$(WHITE)Compiling ${notdir $<} in $(SRC_DIR)"
	@$(CC) $(CFLAGS) $(INC_MS) $(INC) -c $< -o $@

$(OBJF):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p  $(OBJ_DIRS)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX) $(INC) -lXext -lX11 -lm
	@echo "$(GREEN)cub3d compiled!$(DEF_COLOR)"

# $(B_PATH):
# 	@mkdir $(B_PATH)

libft:
	@make -sC $(LIBFT_PATH)

$(LIBFT):
	@echo "Making libft..."
	@make -sC $(LIBFT_PATH)

$(MLX):
	@echo "Making mlx..."
	@make -sC $(MLX_PATH)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(B_PATH)
	@make clean -sC $(LIBFT_PATH)
	@make clean -sC $(MLX_PATH)
	@echo "$(BLUE)cub3d object files cleaned!$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -sC $(LIBFT_PATH)
	@echo "$(CYAN)cub3d executable files cleaned!$(DEF_COLOR)"

re: fclean all
	@echo "$(GREEN)Cleaned and rebuilt everything for cub3d!$(DEF_COLOR)"

norm:
	@norminette $(SRC) | grep -v Norme -B1 || true

.PHONY: all clean fclean re norm libft