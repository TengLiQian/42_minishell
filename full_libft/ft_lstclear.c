/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:03:17 by jolai             #+#    #+#             */
/*   Updated: 2023/09/20 18:51:46 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;

	if (!del || !lst || !*lst)
		return ;
	while (*lst != NULL)
	{
		del((*lst)->content);
		ptr = *lst;
		*lst = ptr->next;
		free(ptr);
	}
}
