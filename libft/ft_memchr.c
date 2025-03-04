/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugi <ahugi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:51:52 by ahugi             #+#    #+#             */
/*   Updated: 2024/11/11 12:54:06 by ahugi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char		*temp_src;
	size_t		i;

	i = 0;
	temp_src = (char *)s;
	while (i < n)
	{
		if ((unsigned char)*temp_src == (unsigned char)c)
		{
			return (temp_src);
		}
		temp_src++;
		i++;
	}
	return (0);
}
