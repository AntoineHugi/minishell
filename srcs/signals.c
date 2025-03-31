#include "../includes/minishell.h"
#include "../libft/libft.h"

void	sigint_handler(int sig)
{
	(void)sig;

	write(1, "\n", 1);
	if (isatty(STDIN_FILENO))
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

// void	ignore_signals(int pid)
// {
//     int status;
//     signal(SIGINT, SIG_IGN);
//     waitpid(pid, &status, 0);
//     setup_signals();
// }

// void	restore_default_signals(char **args)
// {
// 	signal(SIGINT, SIG_DFL);
//     signal(SIGQUIT, SIG_DFL);
//     execvp(args[0], args);
//     perror("error");
//     exit(1);
// }
