/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:20:19 by abausa-v          #+#    #+#             */
/*   Updated: 2024/03/06 19:20:20 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	void	*destiny;

	destiny = dest;
	if (dest == 0 && src == 0)
		return (destiny);
	if (dest == src)
		return (destiny);
	if (dest > src)
		while (count--)
			((unsigned char *)dest)[count] = ((unsigned char *)src)[count];
	else
		while (count--)
			*(unsigned char *)dest++ = *(unsigned char *)src++;
	return (destiny);
}
