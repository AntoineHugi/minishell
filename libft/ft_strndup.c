/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargolo <amargolo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:36:57 by amargolo          #+#    #+#             */
/*   Updated: 2025/03/07 13:42:32 by amargolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*ptr;

	if (!s)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (n + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < n)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
