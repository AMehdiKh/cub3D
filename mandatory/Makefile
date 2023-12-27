# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzoheir <mzoheir@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 15:15:43 by ael-khel          #+#    #+#              #
#    Updated: 2023/12/26 16:54:22 by mzoheir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
NAME = cub3D
################################################################################
OBJ_DIR = objs

FILES = main parse_map check_directions check_rgb check_map_content utils graphics bresenham_line ray_casting mini_map player_movements render_walls textures

SRCS = ${addsuffix .c, $(FILES)}

OBJS = ${SRCS:%.c=$(OBJ_DIR)/%.o}
################################################################################
CC = gcc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
################################################################################
LIBFT = LibFT/libft.a

LIBMLX = MLX42/build/libmlx42.a
################################################################################

.PHONY: clean
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(LIBMLX) -Iinclude -lglfw -L"/Users/$(USER)/goinfre/homebrew/opt/glfw/lib" -fsanitize=address -g  -o $@

$(LIBFT):
	$(MAKE) -C LibFT

$(OBJ_DIR)/%.o: %.c cub3d.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) fclean -C LibFT
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: clean all

# $(CC) $(OBJS) $(LIBFT) $(LIBMLX) -ldl -lglfw -pthread -lm -fsanitize=address -static-libasan -o $@
# $(CC) $(OBJS) $(LIBFT) $(LIBMLX) -Iinclude -lglfw -L"/Users/$(USER)/homebrew/opt/glfw/lib" -fsanitize=address -static-libsan -o $@
# cmake -B build && cmake --build build -j4