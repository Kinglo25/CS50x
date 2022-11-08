NAME		=	minishell

PARS		=	main.c \
				parsing/parser.c \
				parsing/ft_strtok.c \
				parsing/ft_strtok_utils.c \
				parsing/utils.c \
				parsing/parser_utils.c \
				parsing/check_env_var.c \
				parsing/check_env_var_utils.c \
				parsing/bin_check.c

EXE			=	exec/handle_bin.c\
				exec/pipes.c \
				exec/heredoc.c \
				exec/utils.c \
				exec/utils_2.c

BIN			=	builtins/echo.c \
				builtins/cd.c \
				builtins/export.c \
				builtins/export_utils.c \
				builtins/unset.c \
				builtins/pwd_env_exit.c \
				builtins/utils.c \
				builtins/utils_2.c \
				builtins/utils_3.c \
				builtins/utils_4.c

LIBFT		= ./libft/

NAMELFT		= ./libft/libft.a

OBJS		=	$(PARS:c=o) $(EXE:c=o) $(BIN:c=o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror  -g3 \

INC			= 	-I./inc/


all:			$(OBJS) $(NAME)

%.o:		%.c
				@echo "Compiling $<"
				@$(CC) $(INC) -I ~/.brew/opt/readline/include -I /usr/local/opt/readline/include $(CFLAGS) -c  $< -o $(<:c=o)
				@echo "Compiling OK!"

$(NAME):	$(OBJS)
				@make all -s -C $(LIBFT)
				@echo "Linking $^"
				@$(CC) -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include $(CFLAGS) $^ ${NAMELFT} -lreadline -o $@
				@echo "Executable created!"

clean:
				@echo "Cleaning objects..."
				@rm -f $(OBJS) $(BONUS_OBJS)
				@echo "Cleaned up!"

fclean:		clean
				@make fclean -s -C ./libft
				@echo "Removing executable..."
				@rm -f $(NAME)
				@echo "Removed!"

re:			fclean all

.PHONY:		all clean fclean re
