CUR_DIR = $(shell pwd)

NAME = minishell

CC = cc

RM = rm -f

CFLAGS += -Wall -Wextra -Werror

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --trace-children=yes

LIBFT_DIR = $(CUR_DIR)/libft

SRCS = $(addprefix $(CUR_DIR)/srcs/, built_in_cd.c built_in_echo.c built_in_env.c \
					built_in_exit.c built_in_export.c built_in_pwd.c built_in_unset.c \
					errors.c executer.c executer_utils.c expander_exit_status.c expander_utils.c \
					expander.c freeing.c input_output.c lexer_utils.c lexer.c main.c parent_child_process.c \
					parser_cmd_create_utils.c parser_cmd_utils.c parser_delete_utils.c parser_redirections.c \
					parser.c run_built_in.c run_cmd.c)

MY_HEADERS = $(CUR_DIR)/includes/minishell.h

OBJS = $(SRCS:.c=.o)

all: $(LIBFT_DIR)/libft.a $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -ltinfo -o $(NAME)

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
