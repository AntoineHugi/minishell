/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugi <ahugi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:58:57 by ahugi             #+#    #+#             */
/*   Updated: 2024/11/14 17:02:54 by ahugi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_elem;

	new_elem = (t_list *)malloc(sizeof(t_list));
	if (!new_elem)
	{
		return (NULL);
	}
	new_elem->content = content;
	new_elem->next = NULL;
	return (new_elem);
}
/*
#include <stdio.h>

int	main()
{
	t_list	*new_elem;
	int	content = 12345;

	new_elem = ft_lstnew(&content);
	if (!new_elem)
	{
		printf("creation failed\n");
	}
	else if (new_elem->next != NULL)
	{
		printf("next not null\n");
	}
	else if (new_elem->content != &content)
	{
		printf("content incorrect\n");
	}
	else
	{
		printf("it worked!\n");
		printf("Here's the content : %i\n", *(int *)new_elem->content);
	}
	free (new_elem);
}*/