CC	=	gcc

RM	=	rm -f

NAME	=	server

CFLAGS	+=	-Wall -Wextra -Werror -std=c99 -pedantic -D_POSIX_C_SOURCE -D_XOPEN_SOURCE

SRCS	=	server.c \
		save_data.c

OBJS	=	$(SRCS:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) -o $(NAME) $(OBJS)

clean	:
		$(RM) $(OBJS) $(NAME)

re	:	clean all

.PHONY	:	all clean re
