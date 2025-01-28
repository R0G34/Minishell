/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:23:13 by abausa-v          #+#    #+#             */
/*   Updated: 2024/03/06 19:23:19 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int					i;
	const unsigned char	caux = (unsigned char)c;

	i = ft_strlen(str) - 1;
	if (caux == '\0')
		return ((char *)&str[i + 1]);
	while (i >= 0)
	{
		if (str[i] == caux)
			return ((char *)&str[i]);
		i--;
	}
	return (NULL);
}
