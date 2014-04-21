##
## Makefile for libsocket in /home/raphy/Development/Epitech/Libraries/libsocket
##
## Made by Raphael De Freitas
## Login   <defrei_r@epitech.net>
##
## Started on  Mon Dec 16 00:00:03 2013 Raphael De Freitas
## Last update Sat Apr 19 02:11:56 2014 raphael defreitas
##

NAME	=	libsocket.a

CC	?=	clang

AR	=	ar rsc

RM	=	rm -rf

SOURCES	=	$(shell find ./sources -type f -name "*.c")

OBJECTS	=	$(SOURCES:.c=.o)

CFLAGS	=	-Wall -Wextra -ansi -pedantic -g -I ./headers

$(NAME)	:	$(OBJECTS)
		$(AR) $(NAME) $(OBJECTS)

all	:	$(NAME)

clean	:
		$(RM) $(OBJECTS)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.phony	:	all clean fclean re
