CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libgnl.a
HEADER = get_next_line.h

SOURCES = get_next_line.c get_next_line_utils.c

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
	@printf "${GREEN}Done Making GNL.                     ${COLOR_OFF}\n"

%.o : %.c $(HEADER)
	@printf "${BLUE}Compiling $<...                       ${COLOR_OFF}\r"
	@$(CC) $(CFLAGS) -I./includes -c $< -o $@

clean :
	@rm -f $(OBJECTS) 
	@printf "${RED}Removed get next line object files.${COLOR_OFF}\n"

fclean :
	@rm -f $(OBJECTS) $(NAME)
	@printf "${RED}Removed get next line object files and get next line library file.${COLOR_OFF}\n"

re : fclean all

.PHONY : fclean re clean all bonus

