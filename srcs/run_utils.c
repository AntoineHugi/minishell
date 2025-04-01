#include "../includes/minishell.h"

int	read_from_stdin(char *str)
{
	if (!ft_strncmp(str, "find", ft_strlen(str)))
		return (0);
	if (!ft_strncmp(str, "ls", ft_strlen(str)))
		return (0);
	if (!ft_strncmp(str, "mkdir", ft_strlen(str)))
		return (0);
	if (!ft_strncmp(str, "mv", ft_strlen(str)))
		return (0);
	if (!ft_strncmp(str, "rm", ft_strlen(str)))
		return (0);
	if (!ft_strncmp(str, "rmdir", ft_strlen(str)))
		return (0);
	if (!ft_strncmp(str, "touch", ft_strlen(str)))
		return (0);
	return (1);
}

void	drain_pipe(int	fd)
{
	char buffer[1024];
	ssize_t read_bytes;

	read_bytes = read(fd, buffer, sizeof(buffer));
	while (read_bytes > 0)
		read_bytes = read(fd, buffer, sizeof(buffer));
	close(fd);
}
