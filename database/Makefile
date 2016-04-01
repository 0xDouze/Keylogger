OC=gcc
NAME=database
CFLAGS +=-Wall -Wextra -Werror -std=c99 -pedantic -O3 -lsqlite3
SRC=database.c

OBJ=$(SRC:.c=.o)

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f database
	rm -f *~ *.o
