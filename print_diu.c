/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_diu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 19:01:34 by smanta            #+#    #+#             */
/*   Updated: 2020/02/07 19:01:46 by smanta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t		handle_spaces(t_convs *p_convs,
		unsigned long long val, int num_len, int sign_arg)
{
	size_t	res;
	int		num_spaces;
	char	c;

	res = 0;
	num_spaces = 0;
	c = ' ';
	if ((p_convs->plus == 1 && sign_arg == 1) || sign_arg == 0
		|| (p_convs->space == 1 && sign_arg == 1))
		num_spaces = -1;
	num_spaces = num_len >= p_convs->precision ? num_spaces + p_convs->width
			- num_len : num_spaces + p_convs->width - p_convs->precision;
	if (p_convs->precision == 0 && val == 0)
		++num_spaces;
	if (p_convs->zero == 1)
		num_spaces = 0;
	while (num_spaces-- > 0)
	{
		write(1, &c, 1);
		++res;
	}
	return (res);
}

static size_t		handle_value(t_convs *p_convs,
		unsigned long long val, int num_len, int sign_arg)
{
	size_t	res;
	char	c;

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
	if (p_convs->zero == 1 && p_convs->precision == -1)
	{
		num_len = c != '\0' ? num_len + 1 : num_len;
		res += print_char_n('0', p_convs->width - num_len);
	}
	if (num_len < p_convs->precision)
		res += print_char_n('0', p_convs->precision - num_len);
	if (p_convs->precision != 0
		|| (p_convs->precision == 0 && val > 0))
		res += p_convs->conversion == 'u'
				? ft_putnbrull((unsigned long long)val) : ft_putnbrull(val);
	return (res + (c ? 1 : 0));
}

static size_t		handle_diu(t_convs *p_convs,
		unsigned long long ullval, int num_len, int sign_arg)
{
	size_t res;

	if (p_convs->minus == 0)
	{
		res = handle_spaces(p_convs, ullval, num_len, sign_arg);
		res += handle_value(p_convs, ullval, num_len, sign_arg);
	}
	else
	{
		res = handle_value(p_convs, ullval, num_len, sign_arg);
		res += handle_spaces(p_convs, ullval, num_len, sign_arg);
	}
	return (res);
}

size_t				print_diu(t_convs *p_convs, va_list *ap)
{
	int					sign_arg;
	long long			llval;
	unsigned long long	ullval;
	int					num_len;

	llval = get_arg(p_convs, ap);
	sign_arg = llval >= 0 ? 1 : 0;
	if (p_convs->conversion == 'u' && sign_arg == 0)
	{
		ullval = (unsigned long long)llval;
		sign_arg = 1;
	}
	else
		ullval = llval < 0 ? -llval : llval;
	num_len = ft_unumlen(ullval);
	if (p_convs->zero == 1 && (p_convs->precision != -1 || p_convs->minus == 1))
		p_convs->zero = 0;
	if (p_convs->plus == 1 && p_convs->space == 1)
		p_convs->space = 0;
	if (p_convs->conversion == 'u' && (!!(p_convs->plus) || !!(p_convs->space)))
	{
		p_convs->plus = 0;
		p_convs->space = 0;
	}
	return (handle_diu(p_convs, ullval, num_len, sign_arg));
}
