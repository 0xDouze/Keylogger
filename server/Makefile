CC	=	gcc

RM	=	rm -f

NAME	=	server

CFLAGS	+=	-Wall -Wextra -Werror -std=c99 -pedantic -D_GNU_SOURCE -lsqlite3 

SRCS	=	server.c \
				save_data.c \
				parser.c

OBJS	=	$(SRCS:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) -o $(NAME) $(OBJS)

clean	:
		$(RM) $(OBJS) $(NAME)

re	:	clean all

.PHONY	:	all clean re
