#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

void	sig_handler(int signum)
{
	printf("%d\n", signum);
	if (signum == SIGINT)
	{
		printf("ctrl + C\n");
		write(STDOUT_FILENO, "\n",1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(void)
{
	struct sigaction sigint;
	char	*line;

	sigint.sa_handler = sig_handler;
	sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sigint, NULL);
	while (1)
	{
		line = readline(">>");
		if (line == NULL)
			break ;
		free(line);
	}
	free(line);
	write(1,"EXIT\n",6);
	return (0);
}
