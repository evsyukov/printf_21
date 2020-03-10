/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 19:00:13 by smanta            #+#    #+#             */
/*   Updated: 2020/02/07 19:00:17 by smanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t		handle_spaces(t_convs *p_convs, int num_len, int sign_arg)
{
	int		num_spaces;

	num_spaces = 0;
	if ((p_convs->plus == 1 && sign_arg == 1) || sign_arg == 0
		|| (p_convs->space == 1 && sign_arg == 1))
		num_spaces = -1;
	num_spaces = num_len >= p_convs->precision ? num_spaces + p_convs->width
			- num_len : num_spaces + p_convs->width - p_convs->precision;
	if (p_convs->zero == 1)
		num_spaces = 0;
	return (print_char_n(' ', num_spaces));
}

static size_t		handle_value(t_convs *p_convs,
		char *sval, int num_len, int sign_arg)
{
	size_t	res;
	char	c;
	int		index;

	res = 0;
	c = '\0';
	if (p_convs->plus == 1 && sign_arg == 1)
		c = '+';
	else if (sign_arg == 0)
		c = '-';
	else if (p_convs->space == 1 && sign_arg == 1)
		c = ' ';
	if (c)
		write(1, &c, 1);
	if (p_convs->zero == 1 && !(index = 0))
	{
		num_len = c != '\0' ? num_len + 1 : num_len;
		while (p_convs->width - num_len - index++ > 0)
		{
			write(1, "0", 1);
			++res;
		}
	}
	ft_putstr(sval);
	return (res + ft_strlen(sval) + (c ? 1 : 0));
}

static size_t		print_float(t_convs *p_convs, char *sval, int sign_arg)
{
	size_t	res;
	int		num_len;

	res = 0;
	num_len = ft_strlen(sval);
	if (p_convs->zero == 1 && p_convs->minus == 1)
		p_convs->zero = 0;
	if (p_convs->plus == 1 && p_convs->space == 1)
		p_convs->space = 0;
	if (p_convs->minus == 0)
	{
		res += handle_spaces(p_convs, num_len, sign_arg);
		res += handle_value(p_convs, sval, num_len, sign_arg);
	}
	else
	{
		res += handle_value(p_convs, sval, num_len, sign_arg);
		res += handle_spaces(p_convs, num_len, sign_arg);
	}
	return (res);
}

static long double	letsround(int precision, long double dval)
{
	long		index;
	long double	back_pow;

	back_pow = 1;
	index = precision;
	while (index--)
		back_pow /= 10.0;
	return (dval + (0.5 * back_pow));
}

size_t				letsprint_f(t_convs *p_convs, va_list *ap)
{
	size_t		res;
	long double	dval;
	int			sign_arg;
	char		*sval;

	sign_arg = 1;
	p_convs->precision = p_convs->precision == -1 ? 6 : p_convs->precision;
	if (p_convs->length == 3)
		dval = va_arg(*ap, long double);
	else
		dval = va_arg(*ap, double);
	if (dval <= 0)
	{
		sign_arg = ((unsigned short)(*((unsigned short*)(&dval) + 4)) >> 15)
				== 1 ? 0 : 1;
		dval = -dval;
	}
	dval = letsround(p_convs->precision, dval);
	sval = get_str_float(p_convs, dval);
	res = print_float(p_convs, sval, sign_arg);
	free(sval);
	return (res);
}
