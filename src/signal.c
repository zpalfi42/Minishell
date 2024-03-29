/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:27:49 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/23 11:55:26 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		if (g_status == 666)
		{
			rl_replace_line("", 1);
			g_status = 130;
		}
		else
		{
			printf("\n");
			rl_replace_line("", 1);
			rl_on_new_line();
			rl_redisplay();
			g_status = 1;
		}
	}
	else if (signum == SIGQUIT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handler_block(int signum)
{
	(void)signum;
	exit(130);
}

int	sig_handler(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return (1);
	term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (1);
	if (signal(SIGINT, handler) == SIG_ERR)
		return (1);
	if (signal(SIGQUIT, handler) == SIG_ERR)
		return (1);
	return (0);
}
