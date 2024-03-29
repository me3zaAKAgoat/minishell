CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
LDLFLAGS = -lll -lgnl -lft -L$(LINKED_LIST) -L$(LIBFT) -L$(GET_NEXT_LINE) $(READLINE)
READLINE_PATH := $(shell brew --prefix readline)
LIB_READLINE = -L"$(READLINE_PATH)/lib"
INCLUDE_READLINE = -I"$(READLINE_PATH)/include"
READLINE = -lreadline

HEADER = includes/minishell.h

SOURCES = src/main.c\
	src/builtins/pwd.c\
	src/builtins/unset.c\
	src/builtins/export.c\
	src/builtins/export_utils.c\
	src/builtins/env.c\
	src/builtins/echo.c\
	src/builtins/cd.c\
	src/builtins/exit.c\
	src/util/dict.c\
	src/util/join_arr.c\
	src/util/ft_isspace.c\
	src/util/prompt.c\
	src/util/here_doc.c\
	src/util/cmd.c\
	src/util/werror.c\
	src/util/number.c\
	src/util/ft_strcmp.c\
	src/util/strutil.c\
	src/lexing/lexer.c\
	src/lexing/token.c\
	src/lexing/env_expansions.c\
	src/lexing/expansion_utils.c\
	src/lexing/expansion_utils2.c\
	src/lexing/append.c\
	src/lexing/util.c\
	src/lexing/syntax_errors.c\
	src/lexing/remove_space_tokens.c\
	src/env/env.c\
	src/env/update_shlvl.c\
	src/signals/signals.c\
	src/parsing/parse.c\
	src/parsing/create_command.c\
	src/execution/handle_builtin.c\
	src/execution/execution.c\
	src/execution/redirection.c\
	src/execution/pipe.c\
	src/execution/bin_cmd.c\

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

$(NAME) : $(OBJECTS)
	@make -C $(LINKED_LIST) --no-print-directory
	@make -C $(GET_NEXT_LINE) --no-print-directory
	@make -C $(LIBFT) --no-print-directory
	@printf "${BLUE}Linking\r${COLOR_OFF}"
	@$(CC) $(CFLAGS) -o $@ $(LIB_READLINE) $(OBJECTS) $(LDLFLAGS)
	@printf "${GREEN}Done Making Minishell.                        ${COLOR_OFF}\n"

%.o : %.c $(HEADER)
	@printf "${BLUE}Compiling $<...\r${COLOR_OFF}"
	@$(CC) $(CFLAGS) -I./includes $(INCLUDE_READLINE) -c $< -o $@

clean :
	@rm -f $(OBJECTS)
	@printf "${RED}Removed minishell object files.${COLOR_OFF}\n"
	@make -C $(LIBFT) clean --no-print-directory 
	@make -C $(LINKED_LIST) clean --no-print-directory 
	@make -C $(GET_NEXT_LINE) clean --no-print-directory 

fclean :
	@rm -f $(OBJECTS) $(NAME) 
	@printf "${RED}Removed minishell object files and Minishell binary.${COLOR_OFF}\n"
	@make -C $(LIBFT) fclean --no-print-directory 
	@make -C $(LINKED_LIST) fclean --no-print-directory 
	@make -C $(GET_NEXT_LINE) fclean --no-print-directory 

re : fclean all

.PHONY : fclean re clean all