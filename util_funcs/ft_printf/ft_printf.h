/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:01:06 by pauldos-          #+#    #+#             */
/*   Updated: 2023/11/20 15:01:14 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int		ft_printf(const char *format, ...);

int		ft_printf_strlen(const char *str);
int		ft_printf_putchar(char c);
int		ft_printf_putstr(char *str);
int		ft_print_int(int n);
int		ft_print_int_u(unsigned int n);
int		ft_p_hex(unsigned int nbr, char *base);
char	*ft_printf_strchr(const char *str, int c);
int		ft_print_ptr(void *nbr, char *base);

#endif
