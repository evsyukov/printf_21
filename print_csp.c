/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_csp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clashund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 09:36:14 by clashund          #+#    #+#             */
/*   Updated: 2020/02/02 09:36:16 by clashund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*get_word(const char *s, size_t n)
{
	char	*res;
	int		i;

	i = -1;
	res = malloc(sizeof(char) * (n + 1));
	if (res == NULL)
		return (NULL);
	while (++i < (int)n)
		res[i] = s[i];
	res[i] = '\0';
	return (res);
}

static int	max_of_tree(int precision, int width, int len)
{
	int max;

	if (precision > 0)
		if (width < 0)
			max = len;
		else
			max = width > len ? width : len;
	else
		max = width > 0 && width > len ? width : len;
	return (max);
}

size_t		print_c(t_convs *p_convs, char cval)
{
	char	*str;
	int		max;
	char	ch;

	max = 0;
	if (p_convs->precision > 0)
		if (p_convs->width < 0)
			max = 1;
		else
			max = p_convs->width > 1 ? p_convs->width : 1;
	else
		max = p_convs->width > 0 && p_convs->width > 1 ? p_convs->width : 1;
	str = ft_strjoin("", &cval);
	if (p_convs->zero && p_convs->minus)
		ch = ' ';
	else
		ch = p_convs->zero > 0 ? '0' : ' ';
	printstralig(str, (int[]){ 1, max, p_convs->minus }, ch);
	free(str);
	return (max);
}

size_t		print_p(t_convs *p, unsigned long pval)
{
	char	*str;
	char	*word;
	int		len;
	int		max;

	if (!pval)
		return (not_pval(p));
	str = ft_lltoa_base(pval, 16);
	if (p->precision > 0 && p->width < (int)ft_strlen(str))
	{
		len = pval_p(p, str);
		free(str);
		return (len);
	}
	word = ft_strmap(str, (char (*)(char)) ft_tolower);
	free(str);
	str = ft_strjoin("0x", word);
	free(word);
	len = ft_strlen(str);
	max = max_of_tree(p->precision, p->width, len);
	printstralig(str, (int[]){ len, max, p->minus }, ' ');
	free(str);
	return (max);
}

size_t		print_s(t_convs *p_convs, char *sval)
{
	int		len;
	int		max;
	char	*word;
	char	ch;

	word = NULL;
	if (p_convs->precision > -1 && sval)
		word = get_word(sval, p_convs->precision);
	else if (p_convs->precision == -1 && sval)
		word = get_word(sval, ft_strlen(sval));
	else if (p_convs->precision > -1 && !sval)
		word = get_word("(null)", p_convs->precision);
	if (p_convs->precision == -1 && !sval)
		word = get_word("(null)", 6);
	len = ft_strlen(word);
	max = max_of_tree(p_convs->precision, p_convs->width, len);
	if (p_convs->zero && p_convs->minus)
		ch = ' ';
	else
		ch = p_convs->zero > 0 ? '0' : ' ';
	printstralig(word, (int[]){ len, max, p_convs->minus }, ch);
	free(word);
	return ((size_t)max);
}
