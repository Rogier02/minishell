NAME			= 	minishell
CFLAGS			= 	-Wall -Wextra -Werror -g #-fsanitize=address
LDFLAGS			= 	-lreadline
CC				= 	cc
RM				= 	rm -f
AR				= 	ar rcs

LIBFT_DIR		= 	libft
LIBFT_A			= 	libft/libft.a

INCLUDES		=	-I	./includes
SRCS_DIR		= 	srcs
SRCS			= 	srcs/main.c \
                    srcs/error/error.c \
                    srcs/error/malloc_error.c \
                    srcs/builtin/ft_cd.c \
                    srcs/builtin/ft_echo.c \
                    srcs/builtin/ft_env.c \
                    srcs/builtin/ft_exit.c \
                    srcs/builtin/ft_export.c \
                    srcs/builtin/ft_pwd.c \
                    srcs/builtin/ft_unset.c \
                    srcs/execution/exec_builtins.c \
                    srcs/execution/exec_externals.c \
                    srcs/execution/exec_externals_2.c \
                    srcs/execution/exec_single_builtin.c \
                    srcs/execution/executor.c \
					srcs/execution/exit_child.c \
                    srcs/execution/open_infile.c \
                    srcs/execution/open_outfile.c \
					srcs/execution/path_utils_2.c \
                    srcs/execution/path_utils.c \
                    srcs/execution/redirect_pipes.c \
                    srcs/execution/restore_std.c \
                    srcs/execution/wachter.c \
					srcs/free/close_and_reset_fd.c \
					srcs/free/close_fds.c \
                    srcs/free/free_cmd_table.c \
                    srcs/free/free_expansion.c \
                    srcs/free/free_minishell.c \
					srcs/free/kill_children.c \
                    srcs/init/get_envp.c \
                    srcs/init/get_pwd.c \
                    srcs/init/init_minishell.c \
                    srcs/init/init_token.c \
                    srcs/lexer/check_quotes.c \
                    srcs/lexer/is_redirect.c \
                    srcs/lexer/lexical_parser.c \
                    srcs/lexer/skip_whitespaces.c \
                    srcs/lexer/expansion/append_char.c \
                    srcs/lexer/expansion/append_exit_code.c \
                    srcs/lexer/expansion/append_home.c \
                    srcs/lexer/expansion/append_pwd.c \
                    srcs/lexer/expansion/append_variable.c \
                    srcs/lexer/expansion/append_variable_2.c \
                    srcs/lexer/expansion/expansion.c \
                    srcs/lexer/expansion/tilde_expansion.c \
					srcs/lexer/populate_data/handle_heredoc/add_line_to_file.c \
                    srcs/lexer/populate_data/handle_heredoc/handle_heredoc.c \
					srcs/lexer/populate_data/handle_heredoc/heredoc_append_char.c\
					srcs/lexer/populate_data/handle_heredoc/heredoc_append_exit_code.c \
					srcs/lexer/populate_data/handle_heredoc/heredoc_append_variable.c \
					srcs/lexer/populate_data/handle_heredoc/heredoc_expansion.c \
                    srcs/lexer/populate_data/handle_command.c \
                    srcs/lexer/populate_data/handle_pipe.c \
                    srcs/lexer/populate_data/handle_quotes.c \
                    srcs/lexer/populate_data/handle_redirect.c \
                    srcs/lexer/populate_data/populate_command_data.c \
                    srcs/lexer/substrings/get_substrings.c \
                    srcs/lexer/syntax_checker/syntax_check.c \
                    srcs/lexer/tokenize/get_next_token.c \
                    srcs/lexer/tokenize/get_token_type.c \
                    srcs/lexer/tokenize/is_delimiter.c \
                    srcs/lexer/tokenize/tokenizer.c \
                    srcs/signals/signal_handlers.c \
                    srcs/signals/signals.c

OBJ_DIR			= 	objs
OBJ_FILES		=	$(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)

all				: $(LIBFT_A) $(NAME)

$(NAME)			: $(OBJ_FILES) $(LIBFT_A)
				$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT_A) -o $@ $(LDFLAGS) 

$(LIBFT_A)		:
				@echo "compiling libft"
				@$(MAKE) -C $(LIBFT_DIR)
# @git submodule update --init --recursive --remote


$(OBJ_DIR)/%.o	: $(SRCS_DIR)/%.c
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean			: 
				@$(MAKE) -C $(LIBFT_DIR) clean
				$(RM) %.o $(OBJ_FILES)
				$(RM) -r $(OBJ_DIR)

fclean			: clean
				@$(MAKE) -C $(LIBFT_DIR) fclean
				$(RM) $(NAME)

re				: fclean all

.PHONY			: all clean fclean re