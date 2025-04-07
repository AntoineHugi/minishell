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
		if (access(cmd_path, F_OK) == 0)
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

void	run_cmd(t_cmd *cmd, char ***envp, int tmp_fd)
{
	char	*path;

	restore_default_signals();
	if (!cmd->full_cmd_args)
		cmd_error(cmd, "syntax error", EXIT_FAILURE);
	if (cmd->full_cmd_args[0][0] == '\0')
		return ;
	else
	{
		if (!read_from_stdin(cmd->full_cmd_args[0]) && tmp_fd != -1)
			drain_pipe(tmp_fd);
		path = fetch_path(*envp);
		if (!path)
			cmd_error(cmd, cmd->full_cmd_args[0], 127);
		cmd->cmd_path = find_command(path, cmd->full_cmd_args[0]);
		if (!cmd->cmd_path)
			cmd_error(cmd, cmd->full_cmd_args[0], 127);
		execve(cmd->cmd_path, cmd->full_cmd_args, *envp);
		cmd_error(cmd, strerror(errno), errno);
	}
}
