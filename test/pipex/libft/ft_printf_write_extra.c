/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write_extra.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:29:31 by abossel           #+#    #+#             */
/*   Updated: 2022/09/21 15:54:05 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_d(int n, int flags, int fd)
{
	int	num;

	num = 0;
	if (n >= 0)
	{
		if (flags & FT_PRINTF_SIGN_POS)
			num += print_c('+', fd);
		else if (flags & FT_PRINTF_SPACE_POS)
			num += print_c(' ', fd);
	}
	num += print_base(n, "0123456789", fd);
	return (num);
}

int	print_x(unsigned int x, int flags, int fd)
{
	int	num;

	num = 0;
	if (x != 0 && flags & FT_PRINTF_HEX_PREFIX)
		num += print_s("0x", fd);
	num += print_base(x, "0123456789abcdef", fd);
	return (num);
}

int	print_ux(unsigned int x, int flags, int fd)
{
	int	num;

	num = 0;
	if (x != 0 && flags & FT_PRINTF_HEX_PREFIX)
		num += print_s("0X", fd);
	num += print_base(x, "0123456789ABCDEF", fd);
	return (num);
}

int	print_p(void *p, int fd)
{
	unsigned char	*s;
	int				zero;
	int				num;
	int				i;

	num = print_s("0x", fd);
	zero = 1;
	s = (unsigned char *)&p;
	i = sizeof(p) - 1;
	while (i >= 0)
	{
		if (!zero || s[i] / 16 != 0)
		{
			num += print_base(s[i] / 16, "0123456789abcdef", fd);
			zero = 0;
		}
		if (!zero || s[i] % 16 != 0 || i == 0)
		{
			num += print_base(s[i] % 16, "0123456789abcdef", fd);
			zero = 0;
		}
		i--;
	}
	return (num);
}
