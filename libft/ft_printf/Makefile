CFILES = ft_printf.c ft_print_format.c ft_putchar.c ft_putstr.c \
ft_putmem.c ft_putnbr_base.c ft_putnbr_int.c ft_len.c
OBJS = ${CFILES:.c=.o}
RM = rm -rf
GCC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a

all: $(NAME)

$(OBJS): $(CFILES)
	$(GCC) $(CFLAGS) -c $(CFILES)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS) 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.SILENT: 