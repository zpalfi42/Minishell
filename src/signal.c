/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:27:49 by zpalfi            #+#    #+#             */
/*   Updated: 2022/06/14 14:22:20 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
	}
	else if (signum == SIGQUIT)
		rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
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
