/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:15:54 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/13 14:32:23 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(t_data *data)
{
	parser(data);
	ast(data);
	free_all(data);
}

int	name_len(char **envp, int z)
{
	int	i;

	i = 0;
	while (envp[z][i])
	{
		if (envp[z][i] == '=')
			break ;
		i++;
	}
	return (i);
}

int	value_len(char **envp, int z)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[z][i] != '=')
		i++;
	i++;
	while (envp[z][i + j] != '\0')
	{
		j++;
	}
	return (j);
}

char	*envp_name(char **envp, int z)
{
	int		i;
	char	*name;

	i = 0;
	name = malloc(sizeof(char) * name_len(envp, z));
	while (envp[z][i])
	{
		if (envp[z][i] == '=')
			break ;
		name[i] = envp[z][i];
		i++;
	}
	return (name);
}

char	*envp_value(char **envp, int z)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	value = malloc(sizeof(char) * value_len(envp, z));
	while (envp[z][i] != '=')
		i++;
	i++;
	while (envp[z][i + j] != '\0')
	{
		value[j] = envp[z][i + j];
		j++;
	}
	return (value);
}

t_list	*init_env(char **envp)
{
	t_list	*env;

	env = ft_lstnew(envp_name(envp, 0), envp_value(envp, 0));
	int i = 1;
	while (envp[i])
	{
		ft_lstadd_back(&env, ft_lstnew(envp_name(envp, i), envp_value(envp, i)));
		i++;
	}
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void) argc;
	(void) argv;
	print_miniconcha();
	data = (t_data *)malloc(sizeof(t_data));
	if (sig_handler())
		return (1);
	data->env = init_env(envp);
	while (42)
	{
		data->count = 0;
		data->word = 0;
		data->line = readline("\033[1;32mminiconcha>$ \033[1;00m");
		if (data->line == 0)
		{
			free(data->line);
			free(data);
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
