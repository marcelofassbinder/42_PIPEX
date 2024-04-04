CFILES = pipex.c free.c ft_split_trim.c
OBJS = ${CFILES:.c=.o}
CFLAGS = -g -Wall -Werror -Wextra  -fPIC
GCC = gcc 
LIBFT = libft
LIBFTA = libft/libft.a
NAME = pipex
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTA)
	$(GCC) $(CFLAGS) $(OBJS) $(LIBFTA) -o $(NAME)
	@echo "\033[032mPIPEX COMPILED\033[0m"

$(LIBFTA): $(LIBFT)
	make -s -C $(LIBFT)

clean:
	$(RM) $(OBJS)
	make clean -s -C $(LIBFT)

fclean: clean
	$(RM) $(NAME)
	make fclean -s -C $(LIBFT)

re: fclean all

.SILENT: