CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
# CFLAGS = -Wall -Wextra -Werror 
NAME = minishell
READLINE = -lreadline

HEADER = includes/minishell.h

SOURCES = src/main.c\
	src/builtins/pwd.c\
	src/builtins/unset.c\
	src/builtins/export.c\
	src/builtins/env.c\
	src/builtins/cd.c\
	src/builtins/exit.c\
	src/util/dict.c\
	src/util/join_arr.c\
	src/util/prompt.c\
	src/util/strip.c\
	src/util/here_doc.c\
	src/util/cmd.c\
	src/lexing/lexer.c\
	src/lexing/token.c\
	src/env/env.c\
	src/signals/signals.c\
	src/parsing/parse.c\
	src/parsing/create_command.c\

OBJECTS = $(SOURCES:.c=.o)

LINKED_LIST = libraries/linked_list

GET_NEXT_LINE = libraries/get_next_line

LIBFT = libraries/libft

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

$(NAME) : linked_list libft get_next_line $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(READLINE) -lll -lgnl -lft -L$(LINKED_LIST) -L$(LIBFT) -L$(GET_NEXT_LINE)

bonus : $(BONUS_NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -I./includes -c $< -o $@

linked_list :
	@echo "${YELLOW}Making linked list library...${COLOR_OFF}"
	@make -C $(LINKED_LIST) > /dev/null
	@echo "${GREEN}Done.${COLOR_OFF}"

get_next_line :
	@echo "${YELLOW}Making get next line library...${COLOR_OFF}"
	@make -C $(GET_NEXT_LINE) > /dev/null
	@echo "${GREEN}Done.${COLOR_OFF}"
	
libft :
	@echo "${YELLOW}Making libft library...${COLOR_OFF}"
	@make -C $(LIBFT) > /dev/null
	@echo "${GREEN}Done.${COLOR_OFF}"

clean :
	rm -f $(OBJECTS)
	@echo "${RED}Make clean libraries${COLOR_OFF}"
	@make -C $(LIBFT) clean > /dev/null 
	@make -C $(LINKED_LIST) clean > /dev/null 
	@make -C $(GET_NEXT_LINE) clean > /dev/null 

fclean :
	rm -f $(OBJECTS) $(NAME) 
	@echo "${RED}Make fclean libraries${COLOR_OFF}"
	@make -C $(LIBFT) fclean > /dev/null 
	@make -C $(LINKED_LIST) fclean > /dev/null 
	@make -C $(GET_NEXT_LINE) fclean > /dev/null 

re : fclean all

.PHONY : fclean re clean all bonus