#include "../includes/minishell.h"

void	update_pwd(char **envp)
{
	int		i;
	char	pwd[1024];
	char	*new_pwd;

	if (getcwd(pwd, sizeof(pwd)))
	{
		new_pwd = ft_strjoin("PWD=", pwd);
		i = 0;
		while (envp[i])
		{
			if (!ft_strncmp(envp[i], "PWD=", 4))
			{
				//free(envp[i]); do this once envp copy is created
				envp[i] = new_pwd;
				break ;
			}
			else
				i++;
		}
	}
	else
		print_error(strerror(errno), errno);
}

void	change_directory(t_command *cmd, char **envp)
{
	char	*home;

	if (!cmd->full_cmd_args[1])
	{
		home = getenv("HOME");
		if (!home)
			print_error("HOME path not set in env. variables", 1);
		if (chdir(home))
			print_error(strerror(errno), errno);
		else
			update_pwd(envp);
	}
	else
	{
		if (chdir(cmd->full_cmd_args[1]))
			print_error(strerror(errno), errno);
		else
			update_pwd(envp);
	}
}
