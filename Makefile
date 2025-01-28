NAME	= minishell

CC		= clang
CFLAGS	= -Werror -Wextra -Wall -gdwarf-4 -g

SRC_PATH = ./srcs/
OBJ_PATH = ./objts/
INC_PATH = ./include/
SRC		= 	main.c \
			shell_init.c \
			env_utils.c \
			env_mngmnt.c \
			command_parser.c \
			token.c \
			token_utils.c \
			check_var.c \
			syntax_validator.c \
			token_list_mod.c \
			token_list_utils.c \
			var_expander.c \
			var_expander_utils.c \
			var_identifier.c \
			quote_manager.c \
			quote_remover.c \
			value_recover.c \
			var_replacer.c \
			command_builder.c \
			word_parser.c \
			echo_args_handler.c \
			echo_args_utils.c \
			command_args.c \
			input_redirection.c \
			truncate_redirection.c \
			append_redirections.c \
			heredoc_handler.c \
			heredoc_utils.c \
			pipe_handler.c \
			cmd_lst_utils.c \
			cmd_lst_utils_cleanup.c \
			export_command.c \
			unset_command.c \
			cd_command.c \
			env_command.c \
			pwd_command.c \
			echo_command.c \
			exit_command.c \
			process_execution.c \
			command_executor.c \
			execute_utils.c \
			path_resolver.c \
			pipe_manager.c \
			io_manager.c \
			exit.c \
			error.c \
			frees.c \
			signal_handler.c \
			debug_tools.c \
			ft_strtrim.c \
			utils.c
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INC		= -I $(INC_PATH) -I $(LIBFT_PATH)

LIBFT_PATH = ./libft/
LIBFT = ./libft/libft.a

all: $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)


$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) -l readline

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	rm -rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all re clean fclean