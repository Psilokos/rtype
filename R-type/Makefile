##
## Makefile for Makefile in /home/lejeun_b/Tools
## 
## Made by stephane lejeune
## Login   <lejeun_b@epitech.net>
## 
## Started on  Wed Dec 17 15:58:15 2014 stephane lejeune
## Last update Wed Dec 14 13:23:04 2016 Stéphane
##

COMP	=	g++

RM	=	rm -rf

OBJ     =	$(SRC:.cpp=.o)

CPPFLAGS	+=	-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -std=c++11 -g3
CPPFLAGS	+= 	-I./Include
#CPPFLAGS	+=	-Wall -Wextra -Werror

NAME	=	R-Type

SRC	=	Source/main.cpp \
		Source/Render.cpp \
		Source/LoadEntity.cpp \
		Source/SetEntity.cpp \
		Source/SetAnimate.cpp \
		Source/InteractScene.cpp \
		Source/AnimatedSprite.cpp \
		Source/Animation.cpp

AOK	=	echo -e "\\033[32mDone\\033[0m"
AKO	=	echo -e "\\033[31mFailed\\033[0m"
BOK	=	echo -e "\\033[32mDeleting OK\\033[0m"
BKO	=	echo -e "\\033[31mDeleting Failed\\033[0m"
COK	=	echo -e "\\033[32mDeleting OK\\033[0m"
CKO	=	echo -e "\\033[31mDeleting Failed\\033[0m"

all:		$(NAME)

$(NAME): 	$(OBJ)
		@$(COMP) -o $(NAME) $(OBJ) $(CPPFLAGS) && $(AOK) || $(AKO)

clean:
		@$(RM) $(OBJ) && $(BOK) || $(BKO)

fclean: 	clean
		@$(RM) $(NAME) && $(COK) || $(CKO)

re:		fclean all

run:		re
		valgrind ./Gomoku

.PHONY:		all clean fclean re
