##
## Makefile for zappy in /home/manu/tek2/systeme_unix/zappy/graphic_client/v1
## 
## Made by Manu
## Login   <manu@epitech.net>
## 
## Started on  Wed Jun 25 09:50:08 2014 Manu
## Last update Tue Jul  1 14:23:08 2014 Manu
##

SRC	=	main.cpp		\
		Monitor.cpp		\
		Window.cpp		\
		SdlGlUtils.cpp		\
		Camera.cpp		\
		Connection.cpp		\
		Skybox.cpp		\
		AStone.cpp		\

NAME	=	graphic_zappy

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS +=	-W -Wall -Wextra -ggdb -g3

IFLAGS	=	-I.

LDFLAGS	=	-lGL -lGLU -lSDL -lSDL_image -lpthread -lm -lboost_regex -lsfml-network

CXX	=	g++ -o

RM	=	rm -f

.cpp.o	:
		g++ -c $(SRC) $(CXXFLAGS) $(IFLAGS) $(LDFLAGS)

$(NAME)	:	$(OBJ)
		$(CXX) $(NAME) $(OBJ) $(CXXFLAGS) $(IFLAGS) $(LDFLAGS)

all	:	$(NAME)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
