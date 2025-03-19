#include "../includes/minishell.h"

static char	*find_command(char *path, char *cmd)
{
	int		i;
	char	**directories;
	char	*buffer;
	char	*cmd_path;

	directories = ft_split(path, ':');
	i = 0;
	while (directories[i])
	{
		buffer = ft_strjoin(directories[i], "/");
		cmd_path = ft_strjoin(buffer, cmd);
		free(buffer);
		if (!access(cmd_path, F_OK))
		{
			free_array(directories);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_array(directories);
	return (NULL);
}

static char	*fetch_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5) && envp[i][5] != '\0')
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void	run_cmd(char *cmd, char **envp)
{
	char	*path;
	char	*cmd_path;
	char	**full_cmd;

	if (cmd[0] == '\0')
		print_error(cmd, 127);
	path = fetch_path(envp);
	if (!path)
		print_error("path not found in envp", EXIT_FAILURE);
	full_cmd = ft_split(cmd, ' ');
	if (!full_cmd)
		print_error("error splitting command", EXIT_FAILURE);
	cmd_path = find_command(path, full_cmd[0]);
	if (!cmd_path)
	{
		free_array((full_cmd));
		free(cmd_path);
		print_error(cmd, 127);
	}
	execve(cmd_path, full_cmd, envp);
	free_array((full_cmd));
	free(cmd_path);
	print_error(strerror(errno), errno);
}
