#include "../includes/minishell.h"

void	run_built_in(t_command *cmd, char **envp)
{
	char	*str;

	str = cmd->full_cmd_args[0];
	if (!ft_strncmp(str, "echo", ft_strlen(str)))
		echo(cmd);
	if (!ft_strncmp(str, "cd", ft_strlen(str)))
		change_directory(cmd, envp);
	if (!ft_strncmp(str, "pwd", ft_strlen(str)))
		print_wd(cmd);
	if (!ft_strncmp(str, "export", ft_strlen(str)))
		export_var(cmd, envp);
	if (!ft_strncmp(str, "unset", ft_strlen(str)))
		unset_var(cmd, envp);
	if (!ft_strncmp(str, "env", ft_strlen(str)))
		print_env(cmd, envp);
	if (!ft_strncmp(str, "exit", ft_strlen(str)))
		own_exit(cmd);
	free_array((cmd->full_cmd_args));
	exit(0);
}
