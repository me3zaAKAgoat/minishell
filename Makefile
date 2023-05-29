CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
NAME = minishell
READLINE = -lreadline

HEADER = includes/minishell.h

MAIN_SOURCE = src/main.c

MAIN_OBJECT = $(MAIN_SOURCE:.c=.o)

LINKED_LIST = libraries/linked_list

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

$(NAME) : linked_list libft  $(MAIN_OBJECT)
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN_OBJECT) $(READLINE) -lll -lft -L$(LINKED_LIST) -L$(LIBFT)

bonus : $(BONUS_NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -I./includes -c $< -o $@

linked_list :
	@echo "${YELLOW}Making linked list library...${COLOR_OFF}"
	@make -C $(LINKED_LIST) > /dev/null
	@echo "${GREEN}Done.${COLOR_OFF}"

libft :
	@echo "${YELLOW}Making libft library...${COLOR_OFF}"
	@make -C $(LIBFT) > /dev/null
	@echo "${GREEN}Done.${COLOR_OFF}"

clean :
	rm -f $(MAIN_OBJECT)
	@echo "${RED}Make clean libraries${COLOR_OFF}"
	@make -C $(LIBFT) clean > /dev/null 
	@make -C $(LINKED_LIST) clean > /dev/null 

fclean :
	rm -f $(MAIN_OBJECT) $(NAME) 
	@echo "${RED}Make fclean libraries${COLOR_OFF}"
	@make -C $(LIBFT) fclean > /dev/null 
	@make -C $(LINKED_LIST) fclean > /dev/null 

re : fclean all

.PHONY : fclean re clean all bonus