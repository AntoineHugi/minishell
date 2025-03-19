CUR_DIR = $(shell pwd)

NAME = minishell

CC = cc

RM = rm -f

CFLAGS += -Wall -Wextra -Werror

LIBFT_DIR = $(CUR_DIR)/libft

SRCS = $(addprefix $(CUR_DIR)/srcs/, main.c expander.c lexer.c)

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

.PHONY: all clean fclean re
