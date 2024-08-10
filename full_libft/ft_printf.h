/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolai <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:47:42 by jolai             #+#    #+#             */
/*   Updated: 2024/01/09 21:52:17 by jolai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdarg.h>

//static int		ft_strlen(const char *str);
void			ft_printchars(va_list ap, char type, int *count);
void			ft_printnbr(long long num, int *count, char *base);
void			ft_ptrconvert(unsigned long long value, int *count);
void			check_specifier(int *count, const char s, va_list ap);
int				ft_printf(const char *str, ...);

#endif
