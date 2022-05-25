#include "minishell.h"

void handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 1);
        rl_redisplay();
    }
}

void	init_data(t_data *data)
{
	data->n_c = 0;
}

void	parser(t_data *data, char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
			data->n_c++;
		i++;
	}
	printf("%d\n", data->n_c);
}

int main(int argc, char **argv, char **envp)
{
    char *line;
	t_data  *data;

	argc = 0;
	argv = NULL;
	envp = NULL;

    data = (t_data *)malloc(sizeof(t_data));
	signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, SIG_IGN);
	signal(SIGINT, handler);
	init_data(data);
	while (42)
	{
		data->n_c = 0;
		line = readline("miniconcha>$ ");
		if (line)
			parser(data, line);
		else
			exit (1);
	}
}
