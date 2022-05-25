/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 12:42:58 by zpalfi            #+#    #+#             */
/*   Updated: 2022/01/18 12:57:04 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		slen;
	char	*d;

	slen = ft_strlen(s1);
	d = malloc(sizeof(char) * slen + 1);
	if (!d)
		return (NULL);
	ft_bzero(d, slen + 1);
	ft_strlcpy(d, s1, slen + 1);
	return (d);
}
