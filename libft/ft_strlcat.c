/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:21:40 by abausa-v          #+#    #+#             */
/*   Updated: 2024/03/06 19:21:44 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_length;
	size_t	src_length;
	size_t	ori_dest_length;

	ori_dest_length = ft_strlen((const char *) dest);
	dest_length = ori_dest_length;
	src_length = ft_strlen((const char *) src);
	i = 0;
	if (size == 0)
		return (src_length);
	if (dest_length > size)
		return (src_length + size);
	while (src[i] != '\0' && dest_length < (size - 1))
	{
		dest[dest_length] = src[i];
		i++;
		dest_length++;
	}
	dest[dest_length] = 0;
	return (src_length + ori_dest_length);
}
