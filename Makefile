NAME			= 	minishell
CFLAGS			= 	-Wall -Wextra -Werror -g #-fsanitize=adress
LDFLAGS			= 	-lreadline
CC				= 	cc
RM				= 	rm -f
AR				= 	ar rcs

LIBFT_DIR		= 	libft
LIBFT_A			= 	libft/libft.a

INCLUDES		=	-I ./includes
SRCS_DIR		= 	srcs
SRCS			= 	srcs/main.c \
					srcs/error/error.c \
					srcs/init/get_envp.c \
					srcs/init/get_pwd.c \
					srcs/init/init_minishell.c \
					srcs/init/init_singals.c \
					srcs/init/init_parsing.c \
					srcs/init/init_token.c \
					srcs/expansion/expansion.c \
					srcs/expansion/append_char.c \
					srcs/expansion/append_exit_code.c \
					srcs/expansion/append_variable.c \
					srcs/expansion/check_quotes.c \
					srcs/parser/parser.c \
					srcs/parser/add_command.c \
					srcs/parser/add_pipe.c \
					srcs/parser/add_redirect.c \
					srcs/parser/handle_heredoc.c \
					srcs/parser/get_token.c \
					srcs/parser/get_token_type.c \
					srcs/parser/open_file.c \
					srcs/parser/quotes.c \
					srcs/parser/skip_whitespaces.c \
					srcs/signals/signal_handlers.c \
					srcs/free/free_expansion.c \
					srcs/free/free_parsing.c \
					srcs/signals/signals.c 

OBJ_DIR			= 	objs
OBJ_FILES		=	$(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)

all				: $(LIBFT_A) $(NAME)

$(NAME)			: $(OBJ_FILES) $(LIBFT_A)
				$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT_A) -o $@ $(LDFLAGS) 

$(LIBFT_A)		:
				@echo "compiling libft"
				@git submodule update --init --recursive --remote
				@$(MAKE) -C $(LIBFT_DIR)


$(OBJ_DIR)/%.o	: $(SRCS_DIR)/%.c
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean			: 
				@$(MAKE) -C $(LIBFT_DIR) clean
				$(RM) %.o $(OBJ_FILES)

fclean			: clean
				@$(MAKE) -C $(LIBFT_DIR) fclean
				$(RM) $(NAME)

re				: fclean all

.PHONY			: all clean fclean re