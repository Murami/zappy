##
## Makefile for zappy in /home/manu/tek2/systeme_unix/zappy/graphic_client/v1
## 
## Made by Manu
## Login   <manu@epitech.net>
## 
## Started on  Wed Jun 25 09:50:08 2014 Manu
## Last update Wed Jun 25 10:24:59 2014 Manu
##

SRC	=	main.cpp		\
		Monitor.cpp		\
		Window.cpp		\

NAME	=	graphic_zappy

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS +=	-W -Wall -Wextra

IFLAGS	=	-I.

LDFLAGS	=	-lSDL -lGL -lGLU

CXX	=	g++ -o

RM	=	rm -f

$(NAME)	:	$(OBJ)
		$(CXX) $(NAME) $(OBJ) $(CXXFLAGS) $(IFLAGS) $(LDFLAGS)

all	:	$(NAME)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
