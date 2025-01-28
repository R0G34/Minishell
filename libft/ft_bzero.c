/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:17:25 by abausa-v          #+#    #+#             */
/*   Updated: 2024/03/06 19:17:26 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *dest, size_t count)
{
	unsigned char	*destiny;
	size_t			i;

	destiny = dest;
	i = 0;
	while (i < count)
	{
		destiny[i] = 0;
		i++;
	}
	return (destiny);
}
/**
 * The function `ft_bzero` sets a block of memory to zero.
 * 
 * @param dest A pointer to the memory block that needs to be zeroed out.
 * @param count The parameter "count" represents the number of bytes
 * to be set to zero in the memory
 * block pointed to by "dest".
 * 
 * @return a pointer to the destination memory block that has been zeroed out.
 */