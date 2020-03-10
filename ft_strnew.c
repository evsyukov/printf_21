/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clashund <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:13:21 by clashund          #+#    #+#             */
/*   Updated: 2020/02/06 12:13:23 by clashund         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	index;

	if (!(size + 1)
			|| (str = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	index = 0;
	while (index <= size)
		*(str + index++) = '\0';
	return (str);
}
