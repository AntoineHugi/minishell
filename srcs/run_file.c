#include "../includes/minishell.h"

/*void	run_file(t_command *cmd, char **envp, int *exit_status, int *tmp_fd)
{
	char	*line;
	int		fd;

	check_input_output(cmd, tmp_fd);
	fd = open(cmd->full_cmd_args[0], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		//redo initial lexer loop
	}
}*/