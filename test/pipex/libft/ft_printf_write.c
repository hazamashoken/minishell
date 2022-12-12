/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 09:30:27 by abossel           #+#    #+#             */
/*   Updated: 2022/09/26 20:37:13 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "ft_printf.h"

int	print_c(char c, int fd)
{
	if (fd != FT_PRINTF_NO_PRINT)
		ft_putchar_fd(c, fd);
	return (1);
}

int	print_s(char *s, int fd)
{
	int	num;

	if (s == NULL)
		return (print_s("(null)", fd));
	num = 0;
	while (s[num] != '\0')
		num += print_c(s[num], fd);
	return (num);
}

int	print_base(long long n, const char *base, int fd)
{
	long long	rad;
	long long	div;
	long long	mod;
	int			num;

	num = 0;
	rad = 0;
	while (base[rad] != '\0')
		rad++;
	div = n / rad;
	mod = n % rad;
	if (n < 0)
	{
		div = -div;
		mod = -mod;
		num += print_c('-', fd);
	}
	if (div != 0)
		num += print_base(div, base, fd);
	num += print_c(base[mod], fd);
	return (num);
}
