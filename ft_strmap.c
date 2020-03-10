/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clashund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:12:38 by clashund          #+#    #+#             */
/*   Updated: 2020/02/06 12:12:40 by clashund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	len;
	size_t	index;
	char	*dest;

	if (s == NULL || f == NULL)
		return (NULL);
	len = 0;
	while (*(s + len) != '\0')
		len++;
	if (!(len + 1)
			|| (dest = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	index = 0;
	while (index < len)
	{
		*(dest + index) = f(*(s + index));
		index++;
	}
	dest[index] = '\0';
	return (dest);
}
