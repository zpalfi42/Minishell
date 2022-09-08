/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_miniconcha.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:09:23 by zpalfi            #+#    #+#             */
/*   Updated: 2022/09/08 13:28:40 by zpalfi           ###   ########.fr       */
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
	while (i < 6)
	{
		line = get_next_line(fd);
		printf("\033[1;34m %s", line);
		free(line);
		i++;
	}
	close(fd);
}
