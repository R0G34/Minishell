/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:19:42 by abausa-v          #+#    #+#             */
/*   Updated: 2024/03/06 19:19:50 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buffer1, const void *buffer2, size_t count)
{
	unsigned char			mem1;
	unsigned char			mem2;
	const unsigned char		*ptr1;
	const unsigned char		*ptr2;

	ptr1 = (const unsigned char *)buffer1;
	ptr2 = (const unsigned char *)buffer2;
	while (count > 0)
	{
		mem1 = *ptr1;
		mem2 = *ptr2;
		if (mem1 < mem2)
			return (mem1 - mem2);
		else if (mem1 > mem2)
			return (mem1 - mem2);
		ptr1++;
		ptr2++;
		count--;
	}
	return (0);
}
