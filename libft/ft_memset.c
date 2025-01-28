/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:20:23 by abausa-v          #+#    #+#             */
/*   Updated: 2024/03/06 19:20:25 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t count)
{
	unsigned char	*destiny;
	size_t			i;

	destiny = dest;
	i = 0;
	while (i < count)
	{
		destiny[i] = (unsigned char)c;
		i++;
	}
	return (destiny);
}
