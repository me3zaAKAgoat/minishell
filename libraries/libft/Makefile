CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

OBJECTS = ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o ft_itoa.o\
 ft_strlen.o ft_memset.o ft_bzero.o ft_memcpy.o ft_memmove.o ft_strlcpy.o ft_strlcat.o\
 ft_toupper.o ft_tolower.o ft_strchr.o ft_strrchr.o ft_strncmp.o ft_memchr.o ft_strmapi.o\
 ft_memcmp.o ft_atoi.o ft_calloc.o ft_strdup.o ft_substr.o ft_strjoin.o ft_split.o\
 ft_striteri.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o\
 ft_strnstr.o ft_strtrim.o

SOURCES = $(OBJECTS:.o=.c)

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
	@printf "${GREEN}Done Making FT.                        ${COLOR_OFF}\n"

%.o : %.c libft.h
	@printf "${BLUE}Compiling $<...                         ${COLOR_OFF}\r"
	@$(CC) $(CFLAGS) -I./includes -c $< -o $@

clean :
	@rm -f $(OBJECTS)
	@printf "${RED}Removed libft object files.${COLOR_OFF}\n"

fclean :
	@rm -f $(OBJECTS) $(NAME)
	@printf "${RED}Removed libft object files and libft library file.${COLOR_OFF}\n"

re : fclean all

.PHONY : fclean re clean all bonus