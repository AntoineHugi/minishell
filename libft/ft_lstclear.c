/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugi <ahugi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:46:10 by ahugi             #+#    #+#             */
/*   Updated: 2024/11/18 12:50:43 by ahugi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*first;
	t_list	*next;

	if (!lst || !del)
		return ;
	first = *lst;
	while (first)
	{
		next = first->next;
		ft_lstdelone(first, del);
		first = next;
	}
	*lst = NULL;
}
