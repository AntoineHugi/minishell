/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugi <ahugi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:27:49 by ahugi             #+#    #+#             */
/*   Updated: 2024/11/07 11:37:02 by ahugi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*ptr;
	int			len;

	len = (int)ft_strlen(s);
	ptr = NULL;
	while (len >= 0)
	{
		if (s[len] == (unsigned char)c)
		{
			ptr = &s[len];
			return ((char *)ptr);
		}
		len--;
	}
	return ((char *)ptr);
}
