# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 15:46:14 by ael-khel          #+#    #+#              #
#    Updated: 2023/10/17 15:46:17 by ael-khel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################################################################################
NAME = so_long

BNAME = so_long_bonus
###############################################################################################################
CC = gcc

CFLAGS = -Wall -Wextra -Werror -MMD
###############################################################################################################
MANDIR = Mandatory

OBJDIR = Mandatory/objs

FILES = main map_check valid_path graphics sprites moves utils

SRCS = $(addsuffix .c,$(FILES))

OBJS = ${SRCS:%.c=$(OBJDIR)/%.o}

MANDEP = ${OBJS:.o=.d}
##############################################################################################################
BONDIR = Bonus

BOBJDIR = Bonus/objs

BFILES = main map_check valid_path graphics sprites moves utils loop_hook enemy

BSRCS = $(addsuffix _bonus.c,$(BFILES))

BOBJS = ${BSRCS:%.c=$(BOBJDIR)/%.o}

BONDEP = ${BOBJS:.o=.d}
##############################################################################################################
LIBFT = ./LibFT/libft.a

LIBMLX = ./MLX42/build/libmlx42.a
##############################################################################################################
.PHONY: clean
man: $(NAME)
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(LIBMLX) -Iinclude -lglfw -L"/Users/ael-khel/homebrew/opt/glfw/lib" -o $@

$(OBJDIR)/%.o: $(MANDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BNAME)
$(BNAME): $(LIBFT) $(BOBJS)
	$(CC) $(BOBJS) $(LIBFT) $(LIBMLX) -Iinclude -lglfw -L"/Users/ael-khel/homebrew/opt/glfw/lib" -o $@

$(BOBJDIR)/%.o: $(BONDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

all: man bonus

$(LIBFT):
	$(MAKE) -C LibFT

sinclude $(MANDEP) $(BONDEP)

clean:
	$(MAKE) fclean -C LibFT
	$(RM) -r $(OBJDIR) $(BOBJDIR)

fclean: clean
	$(RM) $(NAME) $(BNAME)

re: fclean all
