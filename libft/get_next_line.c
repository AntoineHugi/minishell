/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugi <ahugi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:50:51 by ahugi             #+#    #+#             */
/*   Updated: 2024/12/10 12:34:15 by ahugi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*create_line(char *str)
{
	int		count;
	char	*line;

	if (!str)
		return (NULL);
	count = 0;
	while (str[count] && str[count] != '\n')
		count++;
	if (str[count] == '\n')
		count++;
	line = (char *)ft_gnl_calloc(count + 1, sizeof(char));
	if (!line)
		return (NULL);
	ft_gnl_memcpy(line, str, count);
	line[count] = '\0';
	return (line);
}

static int	check_if_n(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*read_file(int fd, char *result)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)ft_gnl_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		result = ft_gnl_strjoin(result, buffer);
		if (!result || check_if_n(result))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read < 0 || (result && !ft_gnl_strlen(result)))
	{
		free(result);
		result = NULL;
		return (NULL);
	}
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*result;
	char		*line;

	if (!result)
		result = NULL;
	if (BUFFER_SIZE < 1 || fd < 0)
	{
		free(result);
		result = NULL;
		return (NULL);
	}
	if (result && check_if_n(result))
	{
		line = create_line(result);
		result = ft_strchr_mod(result);
		return (line);
	}
	result = read_file(fd, result);
	if (!result)
		return (NULL);
	line = create_line(result);
	result = ft_strchr_mod(result);
	return (line);
}
