/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugi <ahugi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:52:40 by ahugi             #+#    #+#             */
/*   Updated: 2024/11/11 10:52:42 by ahugi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp_ptr;
	size_t			i;

	temp_ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		temp_ptr[i] = c;
		i++;
	}
	return (b);
}
