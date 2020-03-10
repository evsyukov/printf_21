/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letsprint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clashund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:15:07 by clashund          #+#    #+#             */
/*   Updated: 2020/02/06 12:15:09 by clashund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	letsprint_csp(t_convs *p_convs, va_list *ap)
{
	char			*sval;
	char			cval;
	unsigned long	pval;
	size_t			res;

	res = 0;
	if (p_convs->conversion == 'c')
	{
		cval = va_arg(*ap, int);
		res += print_c(p_convs, cval);
	}
	else if (p_convs->conversion == 's')
	{
		sval = va_arg(*ap, char *);
		res += print_s(p_convs, sval);
	}
	else if (p_convs->conversion == 'p')
	{
		pval = va_arg(*ap, unsigned long);
		res += print_p(p_convs, pval);
	}
	return (res);
}

size_t	letsprint_dioux(t_convs *p_convs, va_list *ap)
{
	size_t	res;

	res = 0;
	if (p_convs->conversion == 'd' || p_convs->conversion == 'i'
		|| p_convs->conversion == 'u')
		res = print_diu(p_convs, ap);
	else if (p_convs->conversion == 'o' || p_convs->conversion == 'x'
		|| p_convs->conversion == 'X')
		res = print_ox(p_convs, ap);
	return (res);
}
