/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_miniconcha.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:09:23 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/19 12:01:21 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_miniconcha(void)
{
	int		fd;
	int		i;
	char	*line;

	fd = open("./assets/miniconcha2.txt", O_RDONLY);
	i = 0;
	while (i < 7)
	{
		line = get_next_line(fd);
		printf("\033[1;34m %s", line);
		free(line);
		i++;
	}
	close(fd);
}
