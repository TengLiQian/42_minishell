/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:30:41 by jolai             #+#    #+#             */
/*   Updated: 2023/09/19 19:45:51 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t	totalsize;
	void	*space;

	totalsize = num * size;
	space = malloc(totalsize);
	if (!space)
		return (NULL);
	ft_bzero(space, totalsize);
	return (space);
}
