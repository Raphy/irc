##
## Makefile for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc
## 
## Made by raphael defreitas
## Login   <defrei_r@epitech.net>
## 
## Started on  Wed Apr 16 14:28:43 2014 raphael defreitas
## Last update Fri Apr 25 11:41:17 2014 raphael defreitas
##

## Global settings
CC			?=	clang
CXX			?=	clang++
CFLAGS			=	-Wall -Wextra -ansi -pedantic -g
CXXFLAG			=	-Wall -Wextra -ansi -pedantic -g

## Libs settings
LIBS_PATH		=	./libs
LIBS			=	libsocket liblist

## Common settings
COMMON_SOURCES		=	$(shell find ./irc/common/sources -name "*.c" -type f)
COMMON_OBJECTS		=	$(COMMON_SOURCES:.c=.o)
COMMON_CFLAGS		=	-I ./irc/common/headers  -I ./libs/libsocket/headers -I ./libs/liblist/headers

## Server settings
SERVER_NAME		=	server
SERVER_SOURCES		=	$(shell find ./irc/server/sources -name "*.c" -type f)
SERVER_OBJECTS		=	$(SERVER_SOURCES:.c=.o)
SERVER_CFLAGS		=	-I ./irc/server/headers
SERVER_LFLAGS		=	-L ./libs/libsocket -lsocket
SERVER_LFLAGS		+=	-L ./libs/liblist -llist

## Client settings
CLIENT_NAME		=	client
CLIENT_SOURCES		=	$(shell find ./irc/client/sources -name "*.c" -type f)
CLIENT_CXXSOURCES	=	$(shell find ./irc/client/sources -name "*.cpp" -type f)
CLIENT_OBJECTS		=	$(CLIENT_SOURCES:.c=.o)
CLIENT_CXXOBJECTS	=	$(CLIENT_CXXSOURCES:.cpp=.o)
CLIENT_CFLAGS		=	-I ./irc/client/headers
CLIENT_CXXFLAGS		=	-I ./irc/client/headers $(shell pkg-config --cflags gtkmm-3.0)
CLIENT_LFLAGS		=	-L ./libs/libsocket -lsocket
CLIENT_LFLAGS		+=	-L ./libs/liblist -llist
CLIENT_LFLAGS		+=	$(shell pkg-config --libs gtkmm-3.0)

## Global rules
all			:	libraries $(SERVER_NAME) $(CLIENT_NAME)

clean			:	libraries-clean client-clean server-clean

fclean			:	libraries-fclean clean client-fclean server-fclean

re			:	fclean all

## Libraries rules
libraries		:
				$(foreach lib, $(LIBS), make -C $(LIBS_PATH)/$(lib);)
libraries-clean		:
				$(foreach lib, $(LIBS), make clean -C $(LIBS_PATH)/$(lib);)

libraries-fclean	:
				$(foreach lib, $(LIBS), make fclean -C $(LIBS_PATH)/$(lib);)
libraries-re		:
				$(foreach lib, $(LIBS), make re -C $(LIBS_PATH)/$(lib);)

## Client rules
$(CLIENT_NAME)		:	CFLAGS += $(COMMON_CFLAGS) $(CLIENT_CFLAGS)
$(CLIENT_NAME)		:	CXXFLAGS += $(COMMON_CFLAGS) $(CLIENT_CXXFLAGS)
$(CLIENT_NAME)		:	$(COMMON_OBJECTS) $(CLIENT_OBJECTS) $(CLIENT_CXXOBJECTS)
				$(CXX) -o $(CLIENT_NAME) $(COMMON_OBJECTS) $(CLIENT_OBJECTS) $(CLIENT_CXXOBJECTS) $(CLIENT_LFLAGS)

$(CLIENT_NAME)-clean	:
				rm -rf $(COMMON_OBJECTS) $(CLIENT_OBJECTS) $(CLIENT_CXXOBJECTS)

$(CLIENT_NAME)-fclean	:	$(CLIENT_NAME)-clean
				rm -rf $(CLIENT_NAME)

$(CLIENT_NAME)-re	:	$(CLIENT_NAME)-fclean $(CLIENT_NAME)


## Server rules
$(SERVER_NAME)		:	CFLAGS += $(COMMON_CFLAGS) $(SERVER_CFLAGS)
$(SERVER_NAME)		:	$(COMMON_OBJECTS) $(SERVER_OBJECTS)
				$(CC) -o $(SERVER_NAME) $(COMMON_OBJECTS) $(SERVER_OBJECTS) $(SERVER_LFLAGS)

$(SERVER_NAME)-clean	:
				rm -rf $(COMMON_OBJECTS) $(SERVER_OBJECTS)

$(SERVER_NAME)-fclean	:	$(SERVER_NAME)-clean
				rm -rf $(SERVER_NAME)

$(SERVER_NAME)-re	:	$(SERVER_NAME)-fclean $(SERVER_NAME)
