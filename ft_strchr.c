/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clashund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 20:43:17 by clashund          #+#    #+#             */
/*   Updated: 2020/02/05 20:43:20 by clashund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strchr(const char *s1, int c)
{
	size_t			index;
	unsigned char	c_char;
	unsigned char	*src;

	c_char = (unsigned char)c;
	src = (unsigned char *)s1;
	index = 0;
	while (src[index] != '\0')
	{
		if (src[index] == c_char)
			return ((char *)src + index);
		index++;
	}
	if (src[index] == c_char)
		return ((char *)src + index);
	return (NULL);
}
