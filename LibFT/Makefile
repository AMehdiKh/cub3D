NAME = libft.a

OBJ_DIR = objs

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c \
	get_next_line.c get_next_line_utils.c \
	ft_dprintf.c ft_dprintf_utils.c

OBJS = ${SRCS:%.c=$(OBJ_DIR)/%.o}

.PHONY: clean
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) rcs $@ $?

$(OBJ_DIR)/%.o: %.c libft.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all