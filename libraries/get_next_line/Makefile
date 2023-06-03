CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libgnl.a
HEADER = get_next_line.h

SOURCES = get_next_line.c get_next_line_utils.c

OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	ar -rsc $(NAME) $(OBJECTS)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJECTS) 

fclean : clean
	rm -f $(OBJECTS) $(NAME)

re : fclean all

.PHONY : fclean re clean all bonus

