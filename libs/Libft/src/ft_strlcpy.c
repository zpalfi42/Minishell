/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zpalfi <zpalfi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:29:57 by zpalfi            #+#    #+#             */
/*   Updated: 2022/01/17 18:15:38 by zpalfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dst, const char *src, unsigned long int n)
{
	char		*d;
	char		*e;
	const char	*s;

	d = dst;
	e = dst + n;
	s = src;
	while (*s != '\0' && d < e)
		*d++ = *s++;
	if (d < e)
		*d = 0;
	else if (n > 0)
		d[-1] = 0;
	while (*s != '\0')
		s++;
	return (s - src);
}
