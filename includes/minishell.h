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

typedef struct s_redirection {
	char	*name;
	int		redirection_type;
}				t_redirection;

typedef struct s_command {
	int				number_arguments;
	int				pipe_next;
	int				og_stdin;
	int				og_stdout;
	char			**full_cmd_args;
	char			*cmd_path;
	t_redirection	*input;
	t_redirection	*output;
	char			*errorfile;
	char			*limiter;
	void			*next;
}				t_command;

int		expander(t_command *cmd, char **envp);
int		executer(t_command *cmd, char **envp);
int		here_doc_fd(char *limiter);
void	print_error(char *msg, int err_num);
void	free_array(char **array);
void	run_cmd(t_command *cmd, char **envp);
void	child_process(int *pipe_fd, int tmp_fd, t_command *cmd, char **envp);
void	parent_process(int tmp_fd, t_command *cmd, char **envp);
void	handle_infile(t_command *cmd);
void	handle_outfile(t_command *cmd);
void	export_var(t_command *cmd, char **envp);
char	*check_env(char *cmd, char **envp);

#endif
