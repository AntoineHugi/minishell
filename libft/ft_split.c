/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugi <ahugi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:17:51 by ahugi             #+#    #+#             */
/*   Updated: 2024/11/11 15:18:29 by ahugi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_str_count(char const *s, char c)
{
	int	str_count;
	int	flag;

	flag = 0;
	str_count = 0;
	while (*s)
	{
		if (*s == c)
			flag = 0;
		if (*s != c && flag == 0)
		{
			str_count++;
			flag = 1;
		}
		s++;
	}
	return (str_count);
}

static void	ft_fill_grid(char **result, char const *s, char c, int str_count)
{
	int	str_iter;
	int	letter_iter;
	int	flag;

	str_iter = 0;
	flag = 0;
	while (str_iter < str_count)
	{
		letter_iter = 0;
		while (*s != 0 && *s != c)
		{
			result[str_iter][letter_iter] = *s;
			flag = 1;
			s++;
			letter_iter++;
		}
		if (flag == 1)
		{
			flag = 0;
			result[str_iter][letter_iter] = '\0';
			str_iter++;
		}
		s++;
	}
}

static void	ft_letter_count(int *w_arr, char const *s, char c, int s_count)
{
	int	flag;
	int	letter_iter;
	int	s_iter;

	s_iter = 0;
	flag = 0;
	while (s_iter < s_count)
	{
		letter_iter = 0;
		while (*s != '\0' && *s != c)
		{
			letter_iter++;
			s++;
			flag = 1;
		}
		if (flag == 1)
		{
			w_arr[s_iter] = letter_iter;
			s_iter++;
			flag = 0;
		}
		s++;
	}
}

static int	ft_malloc_words(char **result, char const *s, char c, int str_count)
{
	int	s_iter;
	int	*w_arr;

	w_arr = (int *)malloc((str_count) * sizeof(int));
	if (!w_arr)
		return (0);
	ft_letter_count(w_arr, s, c, str_count);
	s_iter = 0;
	while (s_iter < str_count)
	{
		result[s_iter] = (char *)malloc(sizeof(char) * (w_arr[s_iter] + 1));
		if (!result[s_iter])
		{
			s_iter--;
			while (s_iter >= 0)
			{
				free(result[s_iter--]);
			}
			free(w_arr);
			return (0);
		}
		s_iter++;
	}
	free(w_arr);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		str_count;

	if (!s)
		return (NULL);
	str_count = ft_str_count(s, c);
	result = (char **)malloc(sizeof(char *) * (str_count + 1));
	if (!result)
		return (NULL);
	if (str_count)
	{
		if (!ft_malloc_words(result, s, c, str_count))
		{
			free(result);
			return (NULL);
		}
		ft_fill_grid(result, s, c, str_count);
	}
	result[str_count] = NULL;
	return (result);
}
