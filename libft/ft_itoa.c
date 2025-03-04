/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugi <ahugi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:22:48 by ahugi             #+#    #+#             */
/*   Updated: 2024/11/11 17:23:17 by ahugi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_size(int n)
{
	int	num_size;

	num_size = 1;
	if (n < 0)
	{
		num_size++;
	}
	while (n / 10 != 0)
	{
		num_size++;
		n = n / 10;
	}
	return (num_size);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		num_size;
	int		sign;

	sign = 1;
	num_size = ft_num_size(n);
	number = (char *)ft_calloc((num_size + 1), sizeof(char));
	if (!number)
		return (NULL);
	if (n == 0)
		number[0] = '0';
	if (n < 0)
	{
		number[0] = '-';
		sign = -sign;
	}
	while (n != 0)
	{
		number[num_size - 1] = sign * (n % 10) + 48;
		n = n / 10;
		num_size--;
	}
	return (number);
}
