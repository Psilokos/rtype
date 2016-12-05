##
## Makefile for R-Type in /home/lecouv_v/rendu/rtype
##
## Made by Victorien LE COUVIOUR--TUFFET
## Login   <lecouv_v@epitech.eu>
##
## Started on  Mon Nov 28 15:36:12 2016 Victorien LE COUVIOUR--TUFFET
## Last update Mon Dec  5 19:45:12 2016 Victorien LE COUVIOUR--TUFFET
##

NAME_SERVER		= rtype-srv
NAME_CLIENT		= rtype-cli.exe

CXXFLAGS		+= -W -Wall -Werror -Wextra
CXXFLAGS		+= -I $(DIR_INC_SHARED) $(DEBUG)
LDFLAGS			=
LDFLAGS_SERVER		= -Wl,-rpath='$$ORIGIN/$(DIR_LIB)'
LDFLAGS_CLIENT		= -static-libgcc -static-libstdc++

DIR_LIB			= lib/

DIR_INC			= inc/
DIR_INC_SERVER		= $(DIR_INC)server/
DIR_INC_CLIENT		= $(DIR_INC)client/
DIR_INC_SHARED		= $(DIR_INC)shared/

DIR_SRC			= src/
DIR_SRC_SERVER		= $(DIR_SRC)server/
DIR_SRC_SERVER_SHARED	= $(DIR_SRC)server_shared/
DIR_SRC_CLIENT		= $(DIR_SRC)client/
DIR_SRC_CLIENT_SHARED	= $(DIR_SRC)client_shared/

SRCS_SERVER		= test.cpp

SRCS_CLIENT		=

SRCS_SERVER_SHARED	=

SRCS_CLIENT_SHARED	=

OBJS_SERVER		= $(SRCS_SERVER:.cpp=.o)
OBJS_CLIENT		= $(SRCS_CLIENT:.cpp=.o)
OBJS_SERVER_SHARED	= $(SRCS_SERVER_SHARED:.cpp=.o)
OBJS_CLIENT_SHARED	= $(SRCS_CLIENT_SHARED:.cpp=.o)

RM			= rm -f
PRINTF			= @printf

all:			$(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER):		CXX = g++
$(NAME_SERVER):		EXTRA_FLAGS = -I $(DIR_INC_SERVER)
$(NAME_SERVER):		$(OBJS_SERVER) $(OBJS_SERVER_SHARED)
			$(CXX) $(OBJS_SERVER) $(OBJS_SERVER_SHARED) -o $@ $(LDFLAGS) $(LDFLAGS_SERVER)
			$(PRINTF) '\033[1;32m> Server compiled\033[0m\n'

$(NAME_CLIENT):		CXX = x86_64-w64-mingw32-g++
$(NAME_CLIENT):		EXTRA_FLAGS = -I $(DIR_INC_CLIENT)
$(NAME_CLIENT):		$(OBJS_CLIENT) $(OBJS_CLIENT_SHARED)
			$(CXX) $(OBJS_CLIENT) $(OBJS_CLIENT_SHARED) -o $@ $(LDFLAGS) $(LDFLAGS_CLIENT)
			$(PRINTF) '\033[1;32m> Client compiled\033[0m\n'

%.o:			%.cpp
			$(CXX) $(CXXFLAGS) $(EXTRA_FLAGS) -o $@ -c $<

clean:
			$(RM) $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_SERVER_SHARED) $(OBJS_CLIENT_SHARED)
			$(PRINTF) '\033[1;35m> Directory cleaned\033[0m\n'

fclean:			clean
			$(RM) $(NAME_SERVER) $(NAME_CLIENT)
			$(PRINTF) '\033[1;35m> Binaries removed\033[0m\n'

re:			fclean all

.PHONY:			all clean fclean re
