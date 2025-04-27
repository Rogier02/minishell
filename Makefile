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
					srcs/init/init_minishell.c \
					srcs/init/init_singals.c \
					srcs/get/get_envp.c \
					srcs/get/get_pwd.c \
					srcs/error/error.c \
					srcs/signals/handle_signals.c 

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