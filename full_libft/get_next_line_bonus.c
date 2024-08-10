/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:35:58 by jolai             #+#    #+#             */
/*   Updated: 2024/03/07 15:21:04 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif

void	reset_buffer(char *buffer, char *remainder, int position)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strndup(&remainder[position], (ft_strlen(remainder) - position));
	if (temp)
	{
		while (temp[i])
		{
			buffer[i] = temp[i];
			i++;
		}
		free(temp);
	}
	while (i < (BUFFER_SIZE + 1))
	{
		buffer[i] = '\0';
		i++;
	}
	free(remainder);
}

char	*separate_remainder(char *buffer, char *temp)
{
	char	*result;

	if (!buffer)
		return (NULL);
	result = ft_strndup(temp, ft_find_newline(temp));
	reset_buffer(buffer, temp, ft_find_newline(temp));
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*temp;
	int			readsize;

	if (fd < 0 || fd > 1023)
		return (separate_remainder(buffer[fd], NULL));
	if (!buffer[fd])
		buffer[fd] = (char *) ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	temp = ft_strndup(buffer[fd], ft_strlen(buffer[fd]));
	while (ft_find_newline(temp) == 0)
	{
		reset_buffer(buffer[fd], NULL, 0);
		readsize = read(fd, buffer[fd], BUFFER_SIZE);
		if (readsize <= 0)
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
			if (readsize == 0 && ft_strlen(temp) != 0)
				return (temp);
			free(temp);
			return (NULL);
		}
		temp = ft_strjoin_free(temp, buffer[fd]);
	}
	return (separate_remainder(buffer[fd], temp));
}
