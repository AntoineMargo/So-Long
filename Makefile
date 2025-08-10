CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -Ift_printf
MLX_FLAGS = -lmlx -lXext -lX11 -lm -Lft_printf -lftprintf

SRCS = 	main.c \
		so_long.utils.c \
		get_next_line.c \
		get_next_line_utils.c \
		handle_map1.c \
		handle_map2.c \
		game_logic.c \

OBJS = $(SRCS:.c=.o)

NAME = so_long

all: ft_printf $(NAME)

ft_printf/libftprintf.a:
	make -C ft_printf

$(NAME): $(OBJS) ft_printf/libftprintf.a
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS)

%.o: %.c so_long.h get_next_line.h ft_printf/ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C ft_printf clean

fclean: clean
	rm -f $(NAME)
	make -C ft_printf fclean

re: fclean all