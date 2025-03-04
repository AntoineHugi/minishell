/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugi <ahugi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:48:17 by ahugi             #+#    #+#             */
/*   Updated: 2024/11/18 12:52:15 by ahugi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list_start;
	t_list	*new_list_node;
	void	*new_node_content;

	if (!lst || !f || !del)
		return (NULL);
	new_list_start = NULL;
	while (lst)
	{
		new_node_content = f(lst->content);
		new_list_node = ft_lstnew(new_node_content);
		if (!new_list_node)
		{
			del(new_node_content);
			ft_lstclear(&new_list_start, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list_start, new_list_node);
		lst = lst->next;
	}
	return (new_list_start);
}
