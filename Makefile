CFILES = main.c 
OBJS = ${CFILES:.c=.o}
CFLAGS = -Wall -Werror -Wextra -g
GCC = gcc 
PRINTFD = ft_printf
PRINTFA = ft_printf/libftprintf.a
NAME = pipex
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(PRINTFA)
	$(GCC) $(CFLAGS) $(OBJS) $(PRINTFA) -o $(NAME)

$(PRINTFA): $(PRINTFD)
	make -C $(PRINTFD)

clean:
	$(RM) $(OBJS)
	make clean -C $(PRINTFD)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(PRINTFD)

re: fclean all