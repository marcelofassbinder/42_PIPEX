CFILES = source/pipex.c source/error.c source/utils.c source/main.c
OBJS = ${CFILES:.c=.o}
BONUSFILES = bonus/pipex_bonus.c bonus/utils_bonus.c bonus/error_bonus.c bonus/main_bonus.c source/utils.c source/error.c source/pipex.c
OBJSBONUS = ${BONUSFILES:.c=.o}
CFLAGS = -g -Wall -Werror -Wextra
CC = cc 
LIBFT = libft
LIBFTA = libft/libft.a
NAME = pipex
NAMEBONUS = pipex_bonus
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTA)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFTA) -o $(NAME)
	@echo "\033[032mPIPEX COMPILED\033[0m"

$(LIBFTA): $(LIBFT)
	make -s -C $(LIBFT)

bonus: $(NAMEBONUS)

$(NAMEBONUS): $(OBJSBONUS) $(LIBFTA)
	$(CC) $(CFLAGS) $(OBJSBONUS) $(LIBFTA) -o $(NAMEBONUS)
	@echo "\033[032mBONUS COMPILED\033[0m"

clean:
	$(RM) $(OBJS) $(OBJSBONUS)
	make clean -s -C $(LIBFT)
	@echo "\033[032mOBJECTS DELETED\033[0m"

fclean: clean
	$(RM) $(NAME) $(NAMEBONUS)
	make fclean -s -C $(LIBFT)
	@echo "\033[032mPROGRAMS DELETED\033[0m"

re: fclean all

.SILENT: