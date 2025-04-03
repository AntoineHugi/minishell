#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
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
# include <signal.h>

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_redirection
{
	char					*name;
	int						in_or_out;
	int						redirection_type;
	struct s_redirection	*next;
}				t_redirection;

typedef struct s_command
{
	int					pipe_next;
	int					pipe_prev;
	int					og_stdin;
	int					og_stdout;
	int					built_in;
	int					cd;
	int					exit_status;
	int					executable;
	int					number_arguments;
	char				**full_cmd_args;
	char				*cmd_path;
	char				**envp;
	t_redirection		*redir;
	char				*errorfile;
	struct s_command	*next;
}						t_command;

/* Main */
void		process_input(char *input, char **envp, int *exit_status);

/* Signals */
void		sigint_handler(int sig);
void		setup_signals(void);
void		restore_default_signals(void);
void		ignore_signals(int pid, t_command *cmd);

/* Lexer */
t_token		*create_new_token(char *content);
t_token		*token_last(t_token *token);
t_token		*lexer(char *str);
void		delete_unused_contents(t_token **token_list);
void		delete_token_list(t_token **token_list);

/* Parser */
int			handle_redirections(t_token **current_token, t_command *new_cmd);
void		delete_cmd_list(t_command **cmd_list);
t_command	*create_new_cmd(int number_arguments);
int			build_cmd(t_token **current_token, t_command **new_cmd);
t_command	*parser(t_token *token_list);
void		verify_built_in(t_command *new_cmd);
void		verify_executable(t_command *new_cmd);
void		verify_pipe_prev(t_command **cmd_list, t_command *new_cmd);
void		add_cmd_to_list(t_command **list, t_command *new);

/* Quotes removal */
int			remove_full_quotes(t_command **cmd_list);
char		*quotes_inspection(char *str, int *y);

/* Expander */
int			expander(t_command *cmd, char **envp);
char		*check_envp(char *cmd, char **envp);
void		expand_exit_status(t_command *cmd, int exit_status);
void		clean_empty_argument(t_command *cmd);

/* Executer */
void		executer(t_command *cmd, char **envp, int *exit_status);
void		execute_cmd(t_command *cmd, char **envp, int *tmp_fd);
void		run_built_in(t_command *cmd, char **envp, int tmp_fd);
void		run_cmd(t_command *cmd, char **envp, int tmp_fd);
void		run_file(t_command *cmd, char **envp, int *exit_status, int *tmp_fd);
int			convert_exit_status(int exit_status);
int			read_from_stdin(char *str);
void		drain_pipe(int	fd);

/* Input / Output */
int			save_stdin(t_command *cmd);
void		restore_stdin(t_command *cmd);
int			handle_infile(t_command *cmd, t_redirection *redir);
int			handle_outfile(t_redirection *redir);
int			check_input_output(t_command *cmd, int *tmp_fd);

/* Built-in functions */
void		change_directory(t_command *cmd, char **envp);
void		echo(t_command *cmd);
void		print_env(char **envp);
void		own_exit(t_command *cmd);
void		export_var(t_command *cmd, char **envp);
int			check_valid_key(char *str);
char		**realloc_envp(char ***envp);
void		print_wd(t_command *cmd);
void		unset_var(t_command *cmd, char **envp);

/* Free Memory */
void		free_array(char **array);
void		free_cmd(t_command *cmd);
void		free_all_cmds(t_command *cmd);

/* Error Handling */
void		print_error(char *msg);
void		cmd_error(t_command *cmd, char *msg, int err_num);
void		file_error(t_command *cmd, char *msg, int err_num);

#endif
