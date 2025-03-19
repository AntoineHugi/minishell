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
# include <limits.h>

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_redirection {
	char	*name;
	int		redirection_type;
}				t_redirection;

typedef struct s_command {
	int				pipe_next;
	int				pipe_prev;
	int				og_stdin;
	int				og_stdout;
	int				built_in;
	int				cd;
	int				exit_status;
	int				executable;
	int				number_arguments;
	char			**full_cmd_args;
	char			*cmd_path;
	t_redirection	*input;
	t_redirection	*output;
	char			*errorfile;
	void			*next;
}				t_command;

t_token		*create_new_token(char *content);
t_token		*token_last(t_token *token);
t_token		*lexer(char *str);
void 		delete_token_list(t_token **token_list);
int			handle_redirections(t_token **current_token, t_command *new_cmd);
void		delete_cmd_list(t_command **cmd_list);
t_command	*create_new_cmd(t_command **cmd_list, int number_arguments);
int			build_cmd(t_token **current_token, t_command **cmd_list, t_command **new_cmd);
t_command	*parser(t_token *token_list);
int			expander(t_command *cmd, char **envp);
int			executer(t_command *cmd, char **envp, int exit_status);
int			here_doc_fd(char *limiter);
int			save_stdin(t_command *cmd);
void		restore_stdin(t_command *cmd);
void		print_error(char *msg, int err_num);
void		cmd_error(t_command *cmd, char *msg, int err_num);
void		free_array(char **array);
void		free_cmd(t_command *cmd);
void		free_all_cmds(t_command *cmd);
void		run_cmd(t_command *cmd, char **envp);
void		run_built_in(t_command *cmd, char **envp);
void		child_process(int *pipe_fd, int tmp_fd, t_command *cmd, char **envp);
void		parent_process(int tmp_fd, t_command *cmd, char **envp);
void		handle_infile(t_command *cmd);
void		handle_outfile(t_command *cmd);
void		export_var(t_command *cmd, char **envp);
void		print_env(t_command *cmd, char **envp);
void		print_wd(t_command *cmd);
void		echo(t_command *cmd);
char		*check_envp(char *cmd, char **envp);
void		change_directory(t_command *cmd, char **envp);
void		unset_var(t_command *cmd, char **envp);
void		own_exit(t_command *cmd);
void		expand_exit_status(t_command *cmd, int exit_status);

#endif
