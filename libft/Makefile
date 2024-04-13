CFILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
ft_substr.c ft_tolower.c ft_toupper.c ft_strcmp.c ft_isspace.c

OBJS = ${CFILES:.c=.o}

GNLFILES = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c 

GNLOBJS = ${GNLFILES:.c=.o}

OBJSBONUS = ft_lstnew.o ft_lstadd_front.o ft_lstsize.o ft_lstlast.o ft_lstadd_back.o \
ft_lstdelone.o ft_lstclear.o ft_lstiter.o ft_lstmap.o

RM = rm -rf

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fPIC

PRINTFD = ./ft_printf

PRINTFA = ./ft_printf/libftprintf.a

NAME = libft.a

all: $(NAME)

$(PRINTFA): $(PRINTFD)
	make -C $(PRINTFD)

$(NAME): $(OBJS) $(GNLOBJS) $(PRINTFA)
	cp $(PRINTFA) $(NAME)
	ar -rcs $(NAME) $(GNLOBJS) $(OBJS)
	@echo "\033[33mLIBFT COMPILED\033[0m"

clean:
	make clean -s -C $(PRINTFD)
	$(RM) $(OBJS) $(OBJSBONUS) $(GNLOBJS)

fclean: clean
	make fclean -s -C $(PRINTFD)
	$(RM) $(NAME)

re: fclean all

bonus: $(OBJSBONUS) $(NAME)
	ar -vrcs $(NAME) $(OBJSBONUS)

.SILENT: 