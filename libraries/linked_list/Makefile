CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libll.a
HEADER = linked_list.h

SOURCES = ll_clear.c ll_iter.c ll_push.c ll_map.c ll_new.c ll_size.c\
	ll_last.c ll_atindex.c ll_del_one.c ll_unshift.c ll_shift.c\
	ll_pop.c ll_get_index.c

OBJECTS = $(SOURCES:.c=.o)

COLOR_OFF=\033[0m
BLACK=\033[1;30m
RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
PURPLE=\033[1;35m
CYAN=\033[1;36m
WHITE=\033[1;37m

all : $(NAME)

$(NAME) : $(OBJECTS)
	@ar -rsc $(NAME) $(OBJECTS)
	@printf "${GREEN}Done Making LL.                     ${COLOR_OFF}\n"

%.o : %.c $(HEADER)
	@printf "${BLUE}Compiling $<...                      ${COLOR_OFF}\r"
	@$(CC) $(CFLAGS) -I./includes -c $< -o $@

clean :
	@rm -f $(OBJECTS) 
	@printf "${RED}Removed linekd list object files.${COLOR_OFF}\n"

fclean :
	@rm -f $(OBJECTS) $(NAME)
	@printf "${RED}Removed linekd list object files and linked list library file.${COLOR_OFF}\n"

re : fclean all

.PHONY : fclean re clean all bonus

