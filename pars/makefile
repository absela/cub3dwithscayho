#create a makefile to compile source files into an executable called cub3d

NAME = cub3d

SRCS = cub3d.c 

OBJS = $(SRCS:.c=.o)

CC = gcc


# CFLAGS = -Wall -Wextra -Werror -fsanitize=address
CFLAGS = -Wall -Wextra -Werror 

RM = rm -f

.c.o: cub3d.h
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) cub3d.h
	cd libft && make
	cd ..
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) libft/libft.a -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

