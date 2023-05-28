CC = cc
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
CFLAGS =
NAME = minishell
READLINE = -lreadline

HEADERS = ./includes/minishell.h

MAIN_SOURCE = ./src/main.c

MAIN_OBJECT = $(MAIN_SOURCE:.c=.o)

all : $(NAME)

$(NAME) : $(MAIN_OBJECT)
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN_OBJECT) $(READLINE)

bonus : $(BONUS_NAME)

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -I./includes -c $< -o $@

clean :
	rm -f $(MAIN_OBJECT) 

fclean : clean
	rm -f $(NAME) 

re : fclean all

.PHONY : fclean re clean all bonus