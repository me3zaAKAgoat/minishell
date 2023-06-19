CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
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
	src/builtins/handle_builtin.c\
	src/util/dict.c\
	src/util/join_arr.c\
	src/util/prompt.c\
	src/util/strip.c\
	src/util/here_doc.c\
	src/util/cmd.c\
	src/util/ft_strcmp.c\
	src/lexing/lexer.c\
	src/lexing/token.c\
	src/env/env.c\
	src/signals/signals.c\
	src/parsing/parse.c\
	src/parsing/create_command.c\
	src/execution/execution.c\
	src/execution/redirection.c\
	src/execution/pipe.c\
	src/execution/bin_cmd.c\

OBJECTS = $(SOURCES:.c=.o)

LINKED_LIST = libraries/linked_list
GET_NEXT_LINE = libraries/get_next_line
LIBFT = libraries/libft

LDLFLAGS = -lll -lgnl -lft -L$(LINKED_LIST) -L$(LIBFT) -L$(GET_NEXT_LINE) $(READLINE)

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
	@make -C $(LINKED_LIST) --no-print-directory
	@make -C $(GET_NEXT_LINE) --no-print-directory
	@make -C $(LIBFT) --no-print-directory
	@printf "${GREEN}Done Making Minishell files.                        ${COLOR_OFF}\n"
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LDLFLAGS) -L /goinfre/ekenane/.brew/opt/readline/lib

%.o : %.c $(HEADER)
	@printf "${BLUE}Compiling $<...\r${COLOR_OFF}"
	@$(CC) $(CFLAGS) -I./includes -I /goinfre/ekenane/.brew/opt/readline/include -c $< -o $@


clean :
	@rm -f $(OBJECTS)
	@printf "${RED}Removed Minishell binary.${COLOR_OFF}\n"
	@make -C $(LIBFT) clean --no-print-directory 
	@make -C $(LINKED_LIST) clean --no-print-directory 
	@make -C $(GET_NEXT_LINE) clean --no-print-directory 

fclean :
	@rm -f $(OBJECTS) $(NAME) 
	@printf "${RED}Removed object files and Minishell binary.${COLOR_OFF}\n"
	@make -C $(LIBFT) fclean --no-print-directory 
	@make -C $(LINKED_LIST) fclean --no-print-directory 
	@make -C $(GET_NEXT_LINE) fclean --no-print-directory 

re : fclean all

.PHONY : fclean re clean all bonus