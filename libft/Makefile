NAME 				= libft.a
CFLAGS  			= -Wall -Wextra -Werror -g
CC 					= cc
RM					= rm -rf
AR					= ar rcs

INCL_DIR			= incl
INCL				= incl/libft.h \
					incl/ft_printf.h \
					incl/get_next_line.h

SRC_DIR				= src
SRC_LIBFT			= libft
SRC_STRING			= $(SRC_LIBFT)/string
SRC_CLASS			= $(SRC_LIBFT)/class
SRC_MEMORY			= $(SRC_LIBFT)/memory
SRC_OUTPUT			= $(SRC_LIBFT)/output
SRC_LIST			= $(SRC_LIBFT)/list
SRC_FREE			= $(SRC_LIBFT)/free
SRC_GNL				= get_next_line
SRC_FTPRINTF		= ft_printf

DIRS				= $(LIBFT_DIR) $(SRC_GNL) $(SRC_FTPRINTF)
SRC_DIRS			= $(SRC_STRING) $(SRC_CLASS) $(SRC_MEMORY) $(SRC_OUTPUT) $(SRC_LIST) $(SRC_FREE)
					
SRC_FILES			= $(addprefix $(SRC_CLASS)/, \
					ft_isalpha.c \
					ft_isspace.c \
					ft_isdigit.c \
					ft_isalnum.c \
					ft_isascii.c \
					ft_isprint.c \
					ft_tolower.c \
					ft_toupper.c) \
					$(addprefix $(SRC_MEMORY)/, \
					ft_calloc.c \
					ft_memset.c \
					ft_memcpy.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_memmove.c) \
					$(addprefix $(SRC_OUTPUT)/, \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \
					ft_putstr_fd.c \
					ft_putchar_fd.c) \
					$(addprefix $(SRC_STRING)/, \
					ft_atoi.c \
					ft_bzero.c \
					ft_itoa.c \
					ft_strlen.c \
					ft_strlcpy.c \
					ft_strlcat.c \
					ft_strchr.c \
					ft_strrchr.c \
					ft_strncmp.c \
					ft_strnstr.c \
					ft_strdup.c \
					ft_substr.c \
					ft_strjoin.c \
					ft_strtrim.c \
					ft_split.c \
					ft_strmapi.c \
					ft_striteri.c \
					ft_strtol.c \
					ft_char_count.c ) \
					$(addprefix $(SRC_LIST)/, \
					ft_lstnew.c \
					ft_lstadd_front.c \
					ft_lstsize.c \
					ft_lstlast.c \
					ft_lstadd_back.c \
					ft_lstdelone.c \
 					ft_lstclear.c \
					ft_lstiter.c \
					ft_lstmap.c) \
					$(addprefix $(SRC_FREE)/, \
					ft_nullify.c \
					ft_free_array.c ) \
					$(addprefix $(SRC_GNL)/, \
					get_next_line.c \
					get_next_line_utils.c ) \
					$(addprefix $(SRC_FTPRINTF)/, \
					ft_print_char.c \
					ft_print_digit.c \
					ft_print_str.c \
					ft_printf.c )

OBJ_DIR  			= obj
OBJ_FILES			= $(addprefix obj/, $(SRC_FILES:.c=.o))

all					: $(NAME) 

$(NAME)				: $(OBJ_FILES) $(INCL) 
					@$(AR) $(NAME) $?
					@echo "$(GREEN)$(NAME) created $(BLUE)"

$(OBJ_DIR)/%.o		: $(SRC_DIR)/%.c
					@mkdir -p $(addprefix $(OBJ_DIR)/, $(DIRS))
					@mkdir -p $(addprefix $(OBJ_DIR)/$(LIBFT_DIR)/, $(SRC_DIRS))
					@$(CC) $(CFLAGS) -I $(INCL_DIR) -c $< -o $@
					@echo "$(BLUE)$@ created $(BLUE)"

clean				:
					@$(RM) %.o $(OBJ_FILES) 
					@$(RM) %.o $(OBJ_DIR)
					@echo "$(YELLOW)object files removed$(BLUE)"

fclean				: clean
					@$(RM) $(NAME)
					@echo "$(RED)$(NAME) removed$(BLUE)"

re					: fclean all

.PHONY: all clean fclean re

RESET				= \033[0m
RED					= \033[1;91m
GREEN				= \033[1;92m
YELLOW				= \033[1;93m
BLUE				= \033[1;94m
PURPLE				= \033[1;95m
CYAN				= \033[1;96m
WHITE				= \033[1;97m
BLACK				= \033[1;90m