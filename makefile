NAME			= minishell
CFLAGS			= -Wall -Wextra -Werror #-fsanitize=adress
LDFLAGS			= -lreadline
CC				= cc
RM				= rm -f
AR				= ar rcs

LIBFT_DIR		= libft
LIBFT_A			= $(LIBFT_DIR)/libft.a

INCLUDES		= -I ./includes $(LIBFT_A) 
SRCS_PATH		= srcs

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@echo "compiling libft"
	@$(MAKE) -C $(LIBFT_DIR)

