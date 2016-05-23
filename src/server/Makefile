CC	=	gcc

RM	=	rm -f

NAME	=	server

CFLAGS	+=	-Wall -Wextra -Werror -std=c99 -pedantic -D_GNU_SOURCE -lsqlite3 -lpthread  $(GTK_CFLAGS)

GTK_CFLAGS = `pkg-config --cflags --libs gtk+-2.0`

SRCS	=			server.c \
				save_data.c \
				parser.c\
				../database/database.c\
				../database/interface/closeWindow.c\
				../database/interface/infoClientWindow.c\
				../database/interface/mainWindow.c\
				../database/interface/researchClient.c
OBJS	=	$(SRCS:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean	:
		$(RM) $(OBJS) $(NAME)

re	:	clean all

.PHONY	:	all clean re
