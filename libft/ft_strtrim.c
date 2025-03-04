/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugi <ahugi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:59:21 by ahugi             #+#    #+#             */
/*   Updated: 2024/11/11 17:00:02 by ahugi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_sep(char s1, char const *set)
{
	int	trim;
	int	i;

	trim = 0;
	i = 0;
	while (set[i])
	{
		if (s1 == set[i])
		{
			trim = 1;
		}
		i++;
	}
	return (trim);
}

static size_t	ft_start(char const *s1, char const *set)
{
	size_t	start;

	start = 0;
	while (ft_check_sep(s1[start], set) && s1[start])
	{
		start++;
	}
	return (start);
}

static size_t	ft_end(char const *s1, char const *set)
{
	size_t	end;
	size_t	s1_len;

	end = 0;
	s1_len = ft_strlen(s1);
	while (ft_check_sep(s1[s1_len - 1], set) && s1_len > 1)
	{
		end++;
		s1_len--;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*result;

	if (!s1)
	{
		return (NULL);
	}
	i = 0;
	start = ft_start(s1, set);
	end = ft_end(s1 + start, set);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) - start - end + 1));
	if (!result)
	{
		return (NULL);
	}
	while (start < ft_strlen(s1) - end)
	{
		result[i] = s1[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}
