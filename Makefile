CUR_DIR = $(shell pwd)

$(info CUR_DIR is $(CUR_DIR))

NAME = minishell

CC = cc

RM = rm -f

CFLAGS += -Wall -Wextra -Werror -fPIE

VALGRIND_FLAGS = --leak-check=full --trace-children=yes --show-leak-kinds=all --suppressions=supp.supp

LIBFT_DIR = $(CUR_DIR)/libft

SRCS = $(addprefix $(CUR_DIR)/srcs/, built_in_cd.c built_in_echo.c built_in_env.c built_in_exit.c \
					built_in_export_utils.c built_in_export.c built_in_pwd.c built_in_unset.c \
					errors.c execute_cmd.c executer.c expander_exit_status.c expander_utils.c \
					expander.c freeing.c handle_input.c handle_output.c input_output.c lexer_utils.c \
					lexer_word_token.c lexer.c main.c parser_cmd_create_utils.c parser_cmd_utils.c \
					parser_delete_utils.c parser_redirections.c parser.c remove_full_quotes_utils.c \
					remove_full_quotes.c run_built_in.c run_cmd.c run_file.c run_utils.c signals.c pre_parser.c)

MY_HEADERS = $(CUR_DIR)/includes/minishell.h

OBJS = $(SRCS:.c=.o)

all: $(LIBFT_DIR)/libft.a $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -ltinfo -o $(NAME) -pie

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)
	
%.o: %.c $(MY_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean: 	
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re:	fclean all

valgrind: $(LIBFT_DIR)/libft.a $(NAME)
	valgrind $(VALGRIND_FLAGS) ./$(NAME)

.PHONY: all clean fclean re
