# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 15:15:43 by ael-khel          #+#    #+#              #
#    Updated: 2024/01/04 14:57:38 by ael-khel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
NAME = cub3D
B_NAME = cub3D_bonus
################################################################################
M_DIR = Mandatory

M_OBJ_DIR = Mandatory/objs

M_FILES = main parse_map check_map check_map_elements check_map_content \
		graphics ray_casting h_v_intersection player_movements render_walls \
		destroy_data utils

M_SRCS = ${addsuffix .c, $(M_FILES)}

M_OBJS = ${M_SRCS:%.c=$(M_OBJ_DIR)/%.o}
################################################################################
B_DIR = Bonus

B_OBJ_DIR = Bonus/objs

B_FILES = main parse_map check_map check_map_elements check_map_content \
		graphics ray_casting h_v_intersection mini_map player_movements \
		render_walls destroy_data utils

B_SRCS = ${addsuffix _bonus.c, $(B_FILES)}

B_OBJS = ${B_SRCS:%.c=$(B_OBJ_DIR)/%.o}
################################################################################
CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
################################################################################
LIBFT = LibFT/libft.a

LIBMLX = MLX42/build/libmlx42.a
################################################################################

.PHONY: clean

man: $(NAME)

$(NAME): $(LIBFT) $(M_OBJS)
	$(CC) $(M_OBJS) $(LIBFT) $(LIBMLX) -Iinclude -lglfw -L"/Users/$(USER)/homebrew/opt/glfw/lib" -fsanitize=address -static-libsan -o $@

$(M_OBJ_DIR)/%.o: $(M_DIR)/%.c $(M_DIR)/cub3d.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(B_NAME)

$(B_NAME): $(LIBFT) $(B_OBJS)
	$(CC) $(B_OBJS) $(LIBFT) $(LIBMLX) -Iinclude -lglfw -L"/Users/$(USER)/homebrew/opt/glfw/lib" -fsanitize=address -static-libsan -o $@

$(B_OBJ_DIR)/%.o: $(B_DIR)/%.c $(B_DIR)/cub3d_bonus.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

all: man bonus

$(LIBFT):
	$(MAKE) -C LibFT

clean:
	$(MAKE) fclean -C LibFT
	$(RM) -r $(M_OBJ_DIR) $(B_OBJ_DIR)

fclean: clean
	$(RM) $(NAME) $(B_NAME)

re: fclean all

# $(CC) $(OBJS) $(LIBFT) $(LIBMLX) -ldl -lglfw -pthread -lm -fsanitize=address -static-libasan -o $@
# $(CC) $(OBJS) $(LIBFT) $(LIBMLX) -Iinclude -lglfw -L"/Users/$(USER)/homebrew/opt/glfw/lib" -fsanitize=address -static-libsan -o $@
# cmake -B build && cmake --build build -j4