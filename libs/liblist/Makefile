##
## Makefile for liblist in /home/raphy/Epitech/Libraries/liblist
## 
## Made by raphael defreitas
## Login   <defrei_r@epitech.net>
## 
## Started on  Thu Apr 17 18:52:55 2014 raphael defreitas
## Last update Sat Apr 19 02:11:39 2014 raphael defreitas
##

NAME	=	liblist.a

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
