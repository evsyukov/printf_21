/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clashund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:09:40 by clashund          #+#    #+#             */
/*   Updated: 2020/02/06 12:09:41 by clashund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_convs	*init_convs(void)
{
	t_convs *p_convs;

	p_convs = (t_convs *)malloc(sizeof(t_convs));
	p_convs->sharp = 0;
	p_convs->zero = 0;
	p_convs->minus = 0;
	p_convs->space = 0;
	p_convs->plus = 0;
	p_convs->width = 0;
	p_convs->precision = -1;
	p_convs->length = 0;
	p_convs->conversion = 0;
	return (p_convs);
}

size_t	lets_solut(t_convs *p_convs, va_list *ap, int func)
{
	size_t (*funcs[4])(t_convs *, va_list *);

	funcs[0] = &letsprint_csp;
	funcs[1] = &letsprint_dioux;
	funcs[2] = &letsprint_f;
	funcs[3] = &letsprint_percent;
	return ((*funcs[func])(p_convs, ap));
}

size_t	letsprint(t_convs *p_convs, va_list *ap)
{
	size_t	res;
	int		func;

	func = 0;
	if (ft_strchr("csp", p_convs->conversion))
		func = 0;
	else if (ft_strchr("diouxX", p_convs->conversion))
		func = 1;
	else if (ft_strchr("f", p_convs->conversion))
		func = 2;
	else if (p_convs->conversion == '%')
		func = 3;
	res = lets_solut(p_convs, ap, func);
	return (res);
}

size_t	letspars(const char *fmt, size_t index, va_list *ap, size_t *res)
{
	t_convs *p_convs;

	if (fmt[index] == '\0')
		return (0);
	p_convs = init_convs();
	if (is_flag(fmt[index]))
		if (!(index = letspars_flags(fmt, index, p_convs)))
			return (0);
	if (ft_isdigit(fmt[index]) || fmt[index] == '*')
		if (!(index = letspars_width(fmt, index, p_convs, ap)))
			return (0);
	if (fmt[index] == '.' && !(p_convs->precision = 0))
		if (!(index = letspars_precision(fmt, ++index, p_convs, ap)))
			return (0);
	if (is_length(fmt[index]))
		if (!(index = letspars_length(fmt, index, p_convs)))
			return (0);
	if (is_conversion(fmt[index]))
		if (!(index = letspars_conversion(fmt, index, p_convs)))
			return (0);
	*res = *res + letsprint(p_convs, ap);
	free(p_convs);
	return (index);
}

int		ft_printf(const char *fmt, ...)
{
	size_t	res;
	size_t	index;
	va_list	ap;
	size_t	len_fmt;

	res = 0;
	index = 0;
	len_fmt = ft_strlen(fmt);
	va_start(ap, fmt);
	while (index < len_fmt && fmt[index] != '\0')
		if (fmt[index] == '%')
		{
			if (!(index = letspars(fmt, ++index, &ap, &res)))
				return (res);
		}
		else
		{
			write(1, &(fmt[index++]), 1);
			++res;
		}
	va_end(ap);
	return (res);
}
