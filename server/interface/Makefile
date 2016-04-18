CC= gcc
NAME= mainWindow
SRC= mainWindow.c
CFLAGS += -Wall -Wextra -Werror -std=c99 -pedantic -O3 $(GTK_CFLAGS)
GTK_CFLAGS = `pkg-config --cflags --libs gtk+-2.0`
OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(GTK_CFLAGS)

clean:
	rm -f $(OBJ) $(NAME)
