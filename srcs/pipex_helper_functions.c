#include "../includes/minishell.h"

void	print_error(char *msg, int err_num)
{
	int	i;

	i = 0;
	while (msg[i])
		write(2, &msg[i++], 1);
	if (err_num == 127)
		write(2, ": command not found", 20);
	if (err_num == 2)
		write(2, ": No such file or directory", 28);
	write(2, "\n", 1);
	exit (err_num);
}

int	input_validation(int argc)
{
	if (argc < 5)
		print_error("invalid input", EXIT_FAILURE);
	return (1);
}

int	buff_check(char *limiter, char *buffer)
{
	if (!buffer)
		return (0);
	if (!ft_strlen(buffer))
		return (1);
	if (!ft_strncmp(buffer, limiter, ft_strlen(limiter)))
		return (0);
	return (1);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
