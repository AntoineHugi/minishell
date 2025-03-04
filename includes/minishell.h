#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <termcap.h>

typedef struct s_command {
	int			number_arguments;
	char		**full_cmd_args;
	char		*infile;
	char		*outfile;
	char		*errorfile;
	int			redirection_in_type;
	int			redirection_out_type;
	void		*next;
}				t_command;

//int		buff_check(char *limiter, char *buffer);
int		expander(t_command *cmd, char **envp);
int	executer(t_command *cmd, char **envp);
void	print_error(char *msg, int err_num);
void	free_array(char **array);
void	run_cmd(char **full_cmd, char **envp);
void	next_child_process(int *pipe_fd, int tmp_fd, t_command *cmd, char **envp);
void	first_child_process(int *pipe_fd, t_command *cmd, char **envp);
void	parent_process(int tmp_fd, t_command *cmd, char **envp);

#endif