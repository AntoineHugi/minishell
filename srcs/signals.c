#include "../includes/minishell.h"

int	g_status = 0;

static void	extended_sig_handling(int sig)
{
	g_status = 128 + sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	limited_sig_handling(int sig)
{
	g_status = 128 + sig;
	rl_on_new_line();
}

void	restore_default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_base_signals(void)
{
	signal(SIGINT, extended_sig_handling);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_run_signals(void)
{
	signal(SIGINT, limited_sig_handling);
	signal(SIGQUIT, limited_sig_handling);
}
