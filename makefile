FLAGS = -g -Wall -Wextra -Werror -I $(shell brew --prefix readline)/include#-fsanitize=address

NAME = minishell

SRC = main.c \
	lexer/lexer.c	\
	lexer/lex_utils.c	\
	utils/init_link_lst.c \
	utils/util.c \
	builtin/echo.c \
	builtin/cd.c \
	builtin/env.c \
	builtin/pwd.c \
	builtin/built.c \
	parse/parse.c	\
	parse/grammar.c	\
	parse/utils_parse.c \
	control_commands/control.c

OBJ = $(SRC:.c=.o)

LIBFT = ./libft/libft.a

LINKFLAGS = -lreadline -L$(shell brew --prefix readline)/lib

all: 
	$(MAKE) $(NAME) -j

%.o: %.c
	gcc $(FLAGS) -c $^ -o $@

$(NAME): $(OBJ) include/lexer.h
	make -C libft
	gcc  $(OBJ) $(LIBFT) $(FLAGS) -o $(NAME) $(LINKFLAGS)
clean:
	rm -f $(OBJ)
	make clean -C libft

fclean:
	make clean
	rm -f $(NAME)
	rm -f $(LIBFT)
re: fclean all