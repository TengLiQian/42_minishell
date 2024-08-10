/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:47:27 by jolai             #+#    #+#             */
/*   Updated: 2023/09/19 17:01:37 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (ptr[i])
	{
		if (ptr[i] == (char)c)
			return (&ptr[i]);
		i++;
	}
	if (ptr[i] == (char)c && (char)c == '\0')
		return (&ptr[i]);
	return (0);
}
