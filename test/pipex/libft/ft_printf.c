/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 20:57:39 by abossel           #+#    #+#             */
/*   Updated: 2022/09/26 20:37:41 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include "libft.h"
#include "ft_printf.h"

int	print_after_arg(const char *format, int fd)
{
	char	*next_arg;
	int		num;

	if (format == NULL)
		return (0);
	num = 0;
	next_arg = ft_strchr(format, '%');
	while (format != next_arg && *format != '\0')
	{
		num += print_c(*format, fd);
		format++;
	}
	return (num);
}

int	print_arg(const char *format, va_list *argv, int flags, int fd)
{
	int	num;

	num = 0;
	if (format == NULL)
		return (0);
	if (*format == 'c')
		num += print_c((char)va_arg(*argv, int), fd);
	else if (*format == 's')
		num += print_s(va_arg(*argv, char *), fd);
	else if (*format == 'p')
		num += print_p(va_arg(*argv, void *), fd);
	else if (*format == 'd')
		num += print_d(va_arg(*argv, int), flags, fd);
	else if (*format == 'i')
		num += print_d(va_arg(*argv, int), flags, fd);
	else if (*format == 'u')
		num += print_base(va_arg(*argv, unsigned int), "0123456789", fd);
	else if (*format == 'x')
		num += print_x(va_arg(*argv, unsigned int), flags, fd);
	else if (*format == 'X')
		num += print_ux(va_arg(*argv, unsigned int), flags, fd);
	else if (*format == '%')
		num += print_c('%', fd);
	return (num);
}

int	read_flags(const char *format, int *flags)
{
	int	num;

	num = 0;
	while (*format != '\0')
	{
		if (*format == '+')
			*flags |= FT_PRINTF_SIGN_POS;
		else if (*format == ' ')
			*flags |= FT_PRINTF_SPACE_POS;
		else if (*format == '#')
			*flags |= FT_PRINTF_HEX_PREFIX;
		else
			break ;
		format++;
		num++;
	}
	return (num);
}

int	do_print(int fd, const char *format, va_list *argv)
{
	const char	*next_arg;
	int			flags;
	int			num;

	num = 0;
	next_arg = format;
	if (*next_arg != '%')
	{
		num += print_after_arg(next_arg, fd);
		next_arg = ft_strchr(next_arg, '%');
	}
	while (next_arg != NULL)
	{
		next_arg++;
		flags = 0;
		next_arg += read_flags(next_arg, &flags);
		num += print_arg(next_arg, argv, flags, fd);
		next_arg++;
		num += print_after_arg(next_arg, fd);
		next_arg = ft_strchr(next_arg, '%');
	}
	return (num);
}

int	ft_printf(const char *format, ...)
{
	va_list	argv;
	int		num;

	num = 0;
	va_start(argv, format);
	if (format != NULL)
		num = do_print(1, format, &argv);
	va_end(argv);
	return (num);
}
