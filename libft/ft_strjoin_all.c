/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargolo <amargolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:56:46 by amargolo          #+#    #+#             */
/*   Updated: 2025/03/10 13:38:48 by amargolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_all(char **s, char c)
{
	size_t	res_size;
	size_t	si_size;
	char	*result;
	char	*temp;
	int		i;
	
	if (!*s || !s || !s[0])
		return (NULL);
	result = ft_strdup(s[0]);
	if (!result)
		return (NULL);
	i = 1;
	while (s[i])
	{
		res_size = ft_strlen(result);
		si_size = ft_strlen(s[i]);
		temp = result;
		result = (char *)ft_calloc((res_size + si_size + 2), sizeof(char));
		if (!result)
		{
			free(temp);
			return (NULL);
		}
		ft_memcpy(&result[0], temp, res_size);
		ft_memcpy(&result[res_size], &c, 1);
		ft_memcpy(&result[res_size + 1], s[i], si_size);
		free(temp);
		i++;
	}
	return (result);
}
