#include "../includes/minishell.h"

void	update_pwd(t_cmd *cmd, char **envp)
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

static char	*own_getenv(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "HOME=", 5))
			return(envp[i]);
		i++;
	}
	return (NULL);
}

static void	change_to_home(t_cmd *cmd, char **envp)
{
	char	*home;

	home = own_getenv(envp);
	if (!home)
	{
		print_error("Minishell: cd: HOME not set");
		cmd->exit_status = 1;
		return ;
	}
	if (chdir(home) == -1)
		cmd_error(cmd, strerror(errno), errno);
	else
	{
		update_pwd(cmd, envp);
		cmd->exit_status = 0;
	}
}

void	change_directory(t_cmd *cmd, char **envp)
{
	if (!cmd->full_cmd_args[1])
		change_to_home(cmd, envp);
	else if (cmd->full_cmd_args[1] && !cmd->full_cmd_args[2])
	{
		if (chdir(cmd->full_cmd_args[1]) == -1)
		{
			print_error("Minishell: cd: No such file or directory");
			cmd->exit_status = 1;
		}
		else
		{
			update_pwd(cmd, envp);
			cmd->exit_status = 0;
		}
	}
	else
	{
		print_error("Minishell: cd: too many arguments");
		cmd->exit_status = 0;
	}
}
