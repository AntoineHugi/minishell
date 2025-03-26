#include "../includes/minishell.h"

void	update_pwd(t_command *cmd, char **envp)
{
	int		i;
	char	pwd[1024];
	char	*new_pwd;

	if (getcwd(pwd, sizeof(pwd)))
	{
		new_pwd = ft_strjoin("PWD=", pwd);
		if (!new_pwd)
			cmd_error(cmd, strerror(errno), errno);
		i = 0;
		while (envp[i])
		{
			if (!ft_strncmp(envp[i], "PWD=", 4))
			{
				free(envp[i]);
				envp[i] = new_pwd;
				return ;
			}
			else
				i++;
		}
	}
	else
		cmd_error(cmd, strerror(errno), errno);
}

void	change_directory(t_command *cmd, char **envp)
{
	char	*home;

	if (!cmd->full_cmd_args[1])
	{
		home = getenv("HOME");
		if (!home)
			cmd_error(cmd, "HOME path not set in env. variables", 1);
		if (chdir(home) == -1)
			cmd_error(cmd, strerror(errno), errno);
		else
			update_pwd(cmd, envp);
	}
	else if (cmd->full_cmd_args[1] && !cmd->full_cmd_args[2])
	{
		if (chdir(cmd->full_cmd_args[1]) == -1)
			cmd_error(cmd, " No such file or directory", 1);
		else
			update_pwd(cmd, envp);
	}
	else
		cmd_error(cmd, " too many arguments", EXIT_FAILURE);
	cmd->exit_status = 0;
}
