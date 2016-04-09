CC=gcc
NAME=interface
SRC=dataClient.c
CFLAGS =-Wall -Wextra -Werror -std=c99 -pedantic -O3
GTK_CFLAGS = 'pkg-config --cflags gtk+-2.0'
GTK_LDFLAGS = 'pkg-config --libs gtk+-2.0'
OBJ =$(SRC.c=.o)

all:$(NAME)

interface: $(OBJ)
	$(CC) $(SRC) -o $(NAME) $(CFLAGS) $(GTK_CFLAGS) 

#(GTK_CFLAGS)$(GTK_LDFLAGS)
# gcc interface.c -o interface $(pkg-config --libs --cflags gtk+-2.0)
#$(NAME):$(OBJ)
#	$(CC) $(NAME) $(OBJ) -o $(CFLAGS) $(GTK_CFLAGS) $(GTK_LDFLAGS)

clean:
	rm -f interface
	rm -f *~ *.o
