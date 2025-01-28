/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:22:49 by abausa-v          #+#    #+#             */
/*   Updated: 2024/03/06 19:22:54 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*end;
	size_t			length;
	unsigned int	i;

	i = 0;
	length = ft_strlen(s);
	if (!s || !f)
		return (NULL);
	end = (char *)malloc((length + 1) * sizeof(char));
	if (!end)
		return (NULL);
	while (s[i] != '\0')
	{
		end[i] = f(i, s[i]);
		i++;
	}
	end[i] = '\0';
	return (end);
}
