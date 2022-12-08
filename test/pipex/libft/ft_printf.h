/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 08:39:39 by abossel           #+#    #+#             */
/*   Updated: 2022/09/26 20:36:01 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define FT_PRINTF_SIGN_POS 0x1
# define FT_PRINTF_SPACE_POS 0x2
# define FT_PRINTF_HEX_PREFIX 0x4
# define FT_PRINTF_NO_PRINT (-999999)

int		print_c(char c, int fd);
int		print_s(char *s, int fd);
int		print_base(long long n, const char *base, int fd);
int		print_d(int n, int flags, int fd);
int		print_x(unsigned int x, int flags, int fd);
int		print_ux(unsigned int x, int flags, int fd);
int		print_p(void *p, int fd);
int		ft_printf(const char *format, ...);

#endif
