/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:21:03 by jolai             #+#    #+#             */
/*   Updated: 2024/03/30 20:51:49 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include "libft.h"

char	*get_next_line(int fd);
//void	*ft_calloc(size_t num, size_t size);
//int		ft_strlen(char const *s);
size_t	ft_find_newline(char const *s);
char	*ft_strndup(char *s, size_t len);
char	*ft_strjoin_free(char *s1, char *s2);
#endif
