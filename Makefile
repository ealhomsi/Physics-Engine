## Makefile

## Variables
NAME        = triangle
SRC         = main.cpp BadprogTriangle.cpp
OBJ         = $(SRC:.cpp=.o)
CPPFLAGS    = -Wall -Werror -Wextra -pedantic -ansi
LDFLAGS     = -lglut -lGL -lGLU
CC          = g++

## Rules	
$(NAME) : $(OBJ)
    $(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
    
all     : $(NAME)
clean   :
    rm -f $(OBJ)
fclean  : clean
    rm -f $(NAME)
re    : fclean all
r    : re
    rm -f *~
    rm -f *.o
