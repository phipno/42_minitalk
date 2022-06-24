SRC_FILE = server.c client.c
OBJ_FILE = $(SRC_FILE:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: server client

bonus: server client

server: server.o lib
	$(CC) -o $@ $< libft/libft.a

client: client.o lib
	$(CC) -o $@ $< libft/libft.a

lib:
	make bonus -C libft

clean:
	make clean -C ./libft
	rm -f $(OBJ_FILE)

fclean: clean
	make fclean -C ./libft
	rm -f server client libft/libft.a

re: fclean all