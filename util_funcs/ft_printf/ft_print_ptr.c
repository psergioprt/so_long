/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pauldos- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:03:07 by pauldos-          #+#    #+#             */
/*   Updated: 2023/11/20 15:22:15 by pauldos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_hex(unsigned long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

static char	*hex_to_str(unsigned long n, char *base)
{
	int		size;
	char	*hex;

	size = count_hex(n);
	hex = (char *)malloc(sizeof(char) * (size + 1));
	if (!hex)
		return (NULL);
	hex[size] = '\0';
	while (size > 0)
	{
		hex[size - 1] = base[n % 16];
		n = n / 16;
		size--;
	}
	return (hex);
}

int	ft_print_ptr(void *nbr, char *base)
{
	char			*str;
	int				len;

	len = 0;
	if (!nbr)
	{
		ft_printf_putstr("(nil)");
		return (5);
	}
	str = hex_to_str((unsigned long long)nbr, base);
	if ((unsigned long)nbr == 0)
	{
		ft_printf_putchar('0');
	}
	else
	{
		ft_printf_putstr("0x");
		len = ft_printf_putstr(str) + 2;
	}
	free(str);
	return (len);
}
