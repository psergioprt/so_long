/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:04:40 by pauldos-          #+#    #+#             */
/*   Updated: 2023/11/20 15:25:33 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_format(const char *format, int i, va_list args)
{
	if (format[i + 1] == '%')
		return (ft_printf_putchar(format[i + 1]));
	else if (format[i + 1] == 'c')
		return (ft_printf_putchar(va_arg(args, int)));
	else if (format[i + 1] == 's')
		return (ft_printf_putstr(va_arg(args, char *)));
	else if (format[i + 1] == 'i' || format[i + 1] == 'd')
		return (ft_print_int(va_arg(args, int)));
	else if (format[i + 1] == 'u')
		return (ft_print_int_u(va_arg(args, unsigned int)));
	else if (format[i + 1] == 'x' || format[i + 1] == 'X')
	{
		if (format[i + 1] == 'X')
			return (ft_p_hex(va_arg(args, unsigned int), "0123456789ABCDEF"));
		else
			return (ft_p_hex(va_arg(args, unsigned int), "0123456789abcdef"));
	}
	else if (format[i + 1] == 'p')
		return (ft_print_ptr(va_arg(args, void *), "0123456789abcdef"));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		char_len;
	int		i;
	va_list	args;

	i = 0;
	char_len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (ft_printf_strchr("cspdiuxX%", format[i + 1]))
			{
				char_len += ft_printf_format(format, i, args);
				i++;
			}
		}
		else
			char_len += ft_printf_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (char_len);
}
/*
int	main(void)
{
	char			*str;
	char			c;
	int				n;
	unsigned int	n2;
	void	*p;

	str = "is Luka";
	c = 'd';
	n = -2147483648;
	n2 = -123;
	p = (void *)0;

	ft_printf("_my: %% (String) (s) My name %s! | Char (c): %c\n", str, c);
	printf("sys: %% (String) (s) My name %s! | Char (c): %c\n", str, c);
	ft_printf("_my: Number (d) %d | (i): %i | (u): %u\n", n, n, n2);
	printf("Sys: Number (d) %d | (i): %i | (u): %u\n", n, n, n2);
	ft_printf("_my: Pointer (p): %p | Hex(x): %x (X): %X\n", p, n2, n2);
	printf("Sys: Pointer (p): %p | Hex(x): %x (X): %X\n", p, n2, n2);
	return (0);
}*/
