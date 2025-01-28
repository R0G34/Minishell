/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:19:34 by abausa-v          #+#    #+#             */
/*   Updated: 2024/03/06 19:19:38 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *buffer, int c, size_t count)
{
	while (count > 0)
	{
		if (*(unsigned char *)buffer == (unsigned char) c)
		{
			if ((unsigned char)c == '\0')
				return (buffer);
			else
				return (buffer);
		}
		buffer = (unsigned char *)buffer + 1;
		count--;
	}
	return (NULL);
}
