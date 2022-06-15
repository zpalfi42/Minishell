/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:54 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/15 17:14:10 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_data *data)
{
	parser(data);
	ast(data);
	free_all(data);
}

void	routine(t_data *data)
{
	while (42)
	{
		data->count = 0;
		data->word = 0;
		data->line = readline("\033[1;32mminiconcha>$ \033[1;00m");
		if (data->line == 0)
		{
			free_exit(data);
			exit (1);
		}
		if (*data->line != '\0')
		{
			add_history(data->line);
			minishell(data);
		}
		free(data->line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		i;

	i = 0;
	(void) argc;
	(void) argv;
	print_miniconcha();
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_error(data, "Failed malloc :(");
	if (sig_handler())
		return (1);
	while (envp[i] != 0)
		i++;
	data->envp = malloc(sizeof(char *) * i);
	data->first_envp = malloc(sizeof(char *) * i);
	i = 0;
	while (envp[i] != 0)
	{
		data->envp[i] = malloc(sizeof(char) * ft_strlen(envp[i]));
		data->first_envp[i] = malloc(sizeof(char) * ft_strlen(envp[i]));
		ft_strlcpy(data->envp[i], envp[i], (ft_strlen(envp[i]) + 1));
		ft_strlcpy(data->first_envp[i], envp[i], (ft_strlen(envp[i]) + 1));
		i++;
	}
	data->envp[i] = 0;
	data->first_envp[i] = 0;
	routine(data);
}
