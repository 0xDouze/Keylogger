CC= gcc
NAME= mainWindow
SRC= closeWindow.c infoClientWindow.c mainWindow.c researchClient.c
CFLAGS += -Wall -Wextra -Werror -std=c99 -pedantic -O3 $(GTK_CFLAGS)
GTK_CFLAGS = `pkg-config --cflags --libs gtk+-2.0`
OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(GTK_CFLAGS)

clean:
	rm -f $(OBJ) $(NAME)
