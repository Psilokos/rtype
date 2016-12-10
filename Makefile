##
## Makefile for Makefile in /home/rochef_q/bin
## 
## Made by quentin rochefort
## Login   <rochef_q@epitech.net>
## 
## Started on  Tue Mar  3 18:11:26 2015 quentin rochefort
## Last update Sat Dec 10 19:22:48 2016 Quentin Rochefort
##

NAME	= test

CXX	= g++

CXXFLAGS	+= -W -Wall -Wextra -std=c++11
CXXFLAGS	+= -I./inc/server/

DIR_SRCS	= src/server/

SRCS	= $(DIR_SRCS)main.cpp \
	  $(DIR_SRCS)Map.cpp

OBJS	= $(SRCS:.cpp=.o)

RM	= rm -f

PRINTF	= @printf


all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(NAME)
	$(PRINTF) '\033[1;32m> Compiled\033[0m\n'

clean:
	$(RM) $(OBJS)
	$(PRINTF) '\033[1;35m> Directory cleaned\033[0m\n'

fclean: clean
	$(RM) $(NAME)
	$(PRINTF) '\033[1;35m> Remove executable\033[0m\n'

re: fclean all

.PHONY: all clean fclean re
