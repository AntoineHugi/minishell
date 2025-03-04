/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugi <ahugi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:52:09 by ahugi             #+#    #+#             */
/*   Updated: 2024/11/11 12:53:55 by ahugi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	n = sizeof(*s1) * n;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)*(char *)s1 != (unsigned char)*(char *)s2)
		{
			return ((unsigned char)*(char *)s1 - (unsigned char)*(char *)s2);
		}
		s1++;
		s2++;
		i++;
	}
	if (i == n)
		return (0);
	else
		return ((unsigned char)*(char *)s1 - (unsigned char)*(char *)s2);
}
