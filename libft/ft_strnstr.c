/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:23:07 by abausa-v          #+#    #+#             */
/*   Updated: 2024/03/06 19:23:10 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t slen)
{
	size_t	find_len;

	find_len = ft_strlen(find);
	if (find_len == 0)
		return ((char *)str);
	while (*str && slen >= find_len)
	{
		if (ft_strncmp(str, find, find_len) == 0)
			return ((char *)str);
		str++;
		slen--;
	}
	return (NULL);
}
