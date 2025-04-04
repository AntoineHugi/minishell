/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugi <ahugi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:56:46 by amargolo          #+#    #+#             */
/*   Updated: 2025/04/04 12:37:58 by ahugi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_rest(char **s, char *result, char c)
{
	size_t	res_size;
	size_t	si_size;
	char	*temp;
	int		i;

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

char	*ft_strjoin_all(char **s, char c)
{
	char	*result;

	if (!*s || !s || !s[0])
		return (NULL);
	result = ft_strdup(s[0]);
	if (!result)
		return (NULL);
	result = ft_strjoin_rest(s, result, c);
	if (!result)
		return (NULL);
	return (result);
}
