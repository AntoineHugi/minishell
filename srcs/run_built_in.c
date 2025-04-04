#include "../includes/minishell.h"

void	run_built_in(t_cmd *cmd, char **envp, int tmp_fd)
{
	char	*str;

	str = cmd->full_cmd_args[0];
	if (tmp_fd != -1)
		drain_pipe(tmp_fd);
	if (!ft_strncmp(str, "cd", ft_strlen(str)) && !cmd->pipe_prev)
		change_directory(cmd, envp);
	if (!ft_strncmp(str, "echo", ft_strlen(str)))
		echo(cmd);
	if (!ft_strncmp(str, "env", ft_strlen(str)))
		print_env(envp);
	if (!ft_strncmp(str, "exit", ft_strlen(str)) && !cmd->pipe_prev)
		own_exit(cmd);
	if (!ft_strncmp(str, "export", ft_strlen(str)) && !cmd->pipe_prev)
		export_var(cmd, envp);
	if (!ft_strncmp(str, "pwd", ft_strlen(str)))
		print_wd(cmd);
	if (!ft_strncmp(str, "unset", ft_strlen(str)) && !cmd->pipe_prev)
		unset_var(cmd, envp);
}
