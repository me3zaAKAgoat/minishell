CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libll.a
HEADER = linked_list.h

SOURCES = ll_clear.c ll_iter.c ll_push.c ll_map.c ll_new.c ll_size.c\
	ll_last.c ll_atindex.c ll_del_one.c ll_unshift.c ll_shift.c\
	ll_pop.c ll_get_index.c

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

