/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:22:31 by abausa-v          #+#    #+#             */
/*   Updated: 2024/03/06 19:22:34 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = 0;
	while (src[i] != '\0')
		i++;
	if (size == 0)
		return (i);
	while (src[length] != '\0' && length < (size - 1))
	{
		dest[length] = src[length];
		length++;
	}
	dest[length] = '\0';
	return (i);
}
