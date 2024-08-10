/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:58:52 by jolai             #+#    #+#             */
/*   Updated: 2023/09/21 17:14:49 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*new;
	t_list	*current;

	if (!lst || !f)
		return (NULL);
	newlst = NULL;
	current = lst;
	while (current)
	{
		new = ft_lstnew(current->content);
		if (!new)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		new->content = f(new->content);
		new->next = NULL;
		ft_lstadd_back(&newlst, new);
		current = current->next;
	}
	return (newlst);
}
