/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extra_csp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clashund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 14:47:09 by clashund          #+#    #+#             */
/*   Updated: 2020/02/08 14:47:17 by clashund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	not_pval(t_convs *p)
{
	int	len;

	len = 0;
	if (p->width > 0)
	{
		printstralig("0x0", (int[]){3, p->width, p->minus }, ' ');
		return (p->width);
	}
	if (p->precision >= 0)
	{
		write(1, "0x", 2);
		len = p->precision;
		while (len--)
			write(1, "0", 1);
		return (2 + p->precision);
	}
	printstralig("0x0", (int[]){3, 3, p->minus }, ' ');
	return (3);
}

char	*get_p(const char *s, int prec)
{
	int		i;
	int		len;
	char	*res;

	i = -1;
	len = ft_strlen(s);
	res = malloc(sizeof(char) * (prec + 1));
	if (res == NULL)
		return (NULL);
	while (++i < prec - len)
		res[i] = '0';
	while (++i < prec)
		res[i] = s[i - prec + len];
	return (res);
}

size_t	pval_p(t_convs *p, const char *str)
{
	char	*word;
	char	*s;

	write(1, "0x", 2);
	s = ft_strmap(str, (char (*)(char)) ft_tolower);
	word = get_p(s, p->precision);
	write(1, word, ft_strlen(word));
	write(1, s, ft_strlen(s));
	free(word);
	free(s);
	return (p->precision + 2);
}

void	ft_printcharcount(char ch, size_t count)
{
	while (count--)
		write(1, &ch, 1);
}

void	printstralig(char *c, int *arr, char ch)
{
	if (arr[2])
	{
		write(1, c, arr[0]);
		ft_printcharcount(ch, (size_t)(arr[1] - arr[0]));
	}
	else
	{
		ft_printcharcount(ch, (size_t)(arr[1] - arr[0]));
		write(1, c, arr[0]);
	}
}
