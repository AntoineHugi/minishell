/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugi <ahugi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:34:41 by ahugi             #+#    #+#             */
/*   Updated: 2024/11/12 13:36:17 by ahugi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	number;

	if (n == 0)
		write(fd, "0", 1);
	else if (n < 0)
	{
		if (n == -2147483648)
			write(fd, "-2147483648", 11);
		else
		{
			n = -1 * n;
			write(fd, "-", 1);
			ft_putnbr_fd(n, fd);
		}
	}
	else
	{
		if (n >= 10)
		{
			ft_putnbr_fd(n / 10, fd);
		}
		number = n % 10 + 48;
		write(fd, &number, 1);
	}
}
