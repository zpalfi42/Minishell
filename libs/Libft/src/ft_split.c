/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:48:43 by zpalfi            #+#    #+#             */
/*   Updated: 2022/02/18 13:07:22 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*asign_word(char const *s, int k, int i)
{
	char	*d;
	int		j;

	j = 0;
	d = malloc(sizeof(char) * (i - k + 1));
	while (k < i)
	{
		d[j] = s[k];
		j++;
		k++;
	}
	d[j] = '\0';
	return (d);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s)
		return (NULL);
	p = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!p)
		return (NULL);
	i = -1;
	j = 0;
	k = -1;
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && k < 0)
			k = i;
		else if ((s[i] == c || i == ft_strlen(s)) && k >= 0)
		{
			p[j++] = asign_word(s, k, i);
			k = -1;
		}
	}
	p[j] = 0;
	return (p);
}
