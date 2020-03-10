/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_oxX.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clashund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:16:00 by clashund          #+#    #+#             */
/*   Updated: 2020/02/06 12:16:02 by clashund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t				handle_spaces(t_convs *p_convs,
		const char *str, int num_len, int sign_arg)
{
	size_t	res;
	int		num_spaces;
	int		o;

	res = 0;
	num_spaces = (p_convs->plus == 1 && sign_arg == 1) || sign_arg == 0
			|| (p_convs->space == 1 && sign_arg == 1) ? -1 : 0;
	o = p_convs->sharp && p_convs->conversion == 'o' && *str != '0' ? -1 : 0;
	if (p_convs->sharp == 1 && (p_convs->conversion == 'x'
		|| p_convs->conversion == 'X') && *str != '0')
		num_spaces -= 2;
	num_spaces = num_len >= p_convs->precision ? num_spaces + o + p_convs->width
			- num_len : num_spaces + p_convs->width - p_convs->precision;
	if (p_convs->precision == 0 && *str == '0'
		&& !(p_convs->sharp == 1 && p_convs->conversion == 'o' && *str == '0'))
		++num_spaces;
	if (p_convs->zero == 1)
		num_spaces = 0;
	res += print_char_n(' ', num_spaces);
	return (res);
}

static size_t				preprint_data(t_convs *p_convs,
		char *str, int num_len, char c)
{
	size_t	res;
	int		oxx;

	res = 0;
	oxx = 0;
	if (p_convs->sharp == 1 && *str != '0' && p_convs->conversion == 'o')
	{
		oxx = print_char_n('0', 1);
		++res;
	}
	if (p_convs->sharp == 1 && *str != '0'
		&& (p_convs->conversion == 'x' || p_convs->conversion == 'X'))
	{
		p_convs->conversion == 'x' ? write(1, "0x", 2) : write(1, "0X", 2);
		res += 2;
		oxx += 2;
	}
	if (p_convs->zero == 1 && p_convs->precision == -1)
	{
		num_len = c != '\0' ? num_len + 1 : num_len;
		res += print_char_n('0', p_convs->width - num_len - oxx);
	}
	oxx = p_convs->conversion == 'x' || p_convs->conversion == 'X' ? 0 : oxx;
	return (num_len < p_convs->precision ?
	res + print_char_n('0', p_convs->precision - num_len - oxx) : res);
}

static size_t				handle_value(t_convs *p_convs,
		char *str, int num_len, int sign_arg)
{
	size_t	res;
	char	c;
	char	*temp_str;

	res = 0;
	c = p_convs->plus == 1 && sign_arg == 1 ? '+' : '\0';
	c = sign_arg == 0 ? '-' : '\0';
	c = p_convs->space == 1 && sign_arg == 1 ? ' ' : '\0';
	if (c)
		res += print_char_n(c, 1);
	res += preprint_data(p_convs, str, num_len, c);
	if (p_convs->precision != 0
		|| (p_convs->precision == 0 && (num_len > 0 && *str != '0'))
		|| (p_convs->sharp == 1 && p_convs->conversion == 'o' && *str == '0'))
	{
		res += num_len;
		temp_str = ft_strmap(str, (char (*)(char)) ft_tolower);
		p_convs->conversion == 'X' ? ft_putstr(str) : ft_putstr(temp_str);
		free(temp_str);
	}
	return (res);
}

size_t						print_ox(t_convs *p_convs, va_list *ap)
{
	size_t				res;
	unsigned long long	llval;
	char				*str;
	int					num_len;

	llval = get_uarg(p_convs, ap);
	str = p_convs->conversion == 'o'
			? ft_ulltoa_base(llval, 8) : ft_ulltoa_base(llval, 16);
	num_len = ft_strlen(str);
	if (p_convs->zero == 1 && (p_convs->precision != -1 || p_convs->minus == 1))
		p_convs->zero = 0;
	if (p_convs->plus == 1 && p_convs->space == 1)
		p_convs->space = 0;
	if (p_convs->minus == 0)
	{
		res = handle_spaces(p_convs, str, num_len, 1);
		res += handle_value(p_convs, str, num_len, 1);
	}
	else
	{
		res = handle_value(p_convs, str, num_len, 1);
		res += handle_spaces(p_convs, str, num_len, 1);
	}
	free(str);
	return (res);
}
