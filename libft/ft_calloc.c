/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:17:33 by abausa-v          #+#    #+#             */
/*   Updated: 2024/03/06 19:17:44 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t number, size_t size)
{
	void	*assignmem;

	if (number == 0 || size == 0)
		return (malloc (0));
	if (!(number < SIZE_MAX / size))
		return (NULL);
	assignmem = (void *)malloc(number * size);
	if (assignmem == 0)
		return (NULL);
	ft_bzero(assignmem, number * size);
	return (assignmem);
}
