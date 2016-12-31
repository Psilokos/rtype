##
## Makefile for Makefile in /home/rochef_q/bin
## 
## Made by quentin rochefort
## Login   <rochef_q@epitech.net>
## 
## Started on  Tue Mar  3 18:11:26 2015 quentin rochefort
## Last update Sat Dec 31 03:14:13 2016 Quentin Rochefort
##

NAME	= rtype

CXX	= g++

CXXFLAGS	+= -W -Wall -Wextra -std=c++11
CXXFLAGS	+= -I./inc/server/

DIR_SRCS	= src/server/

SRCS	= $(DIR_SRCS)main.cpp	\
	  $(DIR_SRCS)Map.cpp	\
	  $(DIR_SRCS)Weapon.cpp	\
	  $(DIR_SRCS)Block.cpp	\
	  $(DIR_SRCS)Bullet.cpp	\
	  $(DIR_SRCS)Enemy.cpp	\
	  $(DIR_SRCS)SinusoidalPattern.cpp	\
	  $(DIR_SRCS)ACharacter.cpp	\
	  $(DIR_SRCS)Player.cpp

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
