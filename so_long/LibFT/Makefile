NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = \
	ft_printf.c print_spec.c ft_split.c ft_itoa.c ft_calloc.c ft_bzero.c ft_strchr.c \
	ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strncmp.c ft_strlen.c ft_putendl_fd.c ft_memset.c

OBJS = ${SRCS:.c=.o}

.PHONY: clean
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) rcs $@ $?

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all