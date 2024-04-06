CFILES = source/pipex.c source/free.c source/utils.c
OBJS = ${CFILES:.c=.o}
BONUSFILES = bonus/pipex_bonus.c
OBJSBONUS = ${BONUSFILES:.c=.o}
CFLAGS = -g -Wall -Werror -Wextra  -fPIC
GCC = gcc 
LIBFT = libft
LIBFTA = libft/libft.a
NAME = pipex
NAMEBONUS = pipex_bonus
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTA)
	$(GCC) $(CFLAGS) $(OBJS) $(LIBFTA) -o $(NAME)
	@echo "\033[032mPIPEX COMPILED\033[0m"

$(LIBFTA): $(LIBFT)
	make -s -C $(LIBFT)

bonus: $(NAMEBONUS)

$(NAMEBONUS): $(OBJSBONUS) $(LIBFTA)
	$(GCC) $(CFLAGS) $(OBJSBONUS) $(LIBFTA) -o $(NAMEBONUS)
	@echo "\033[032mBONUS COMPILED\033[0m"

clean:
	$(RM) $(OBJS)
	make clean -s -C $(LIBFT)

fclean: clean
	$(RM) $(NAME)
	make fclean -s -C $(LIBFT)

re: fclean all

.SILENT: