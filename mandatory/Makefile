# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 15:15:43 by ael-khel          #+#    #+#              #
#    Updated: 2023/12/18 21:13:31 by ael-khel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
NAME = cub3D
################################################################################
OBJ_DIR = objs

FILES = main parse_map check_directions check_rgb check_map_content utils graphics bresenham_line

SRCS = ${addsuffix .c, $(FILES)}

OBJS = ${SRCS:%.c=$(OBJ_DIR)/%.o}
################################################################################
CC = gcc

CFLAGS = -Wall -Wextra -fsanitize=address -g
################################################################################
LIBFT = LibFT/libft.a

LIBMLX = MLX42/build/libmlx42.a
################################################################################

.PHONY: clean
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(LIBMLX) -Iinclude -lglfw -L"/Users/ael-khel/homebrew/opt/glfw/lib" -fsanitize=address -static-libsan -o $@

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
# $(CC) $(OBJS) $(LIBFT) $(LIBMLX) -Iinclude -lglfw -L"/Users/ael-khel/homebrew/opt/glfw/lib" -fsanitize=address -static-libsan -o $@