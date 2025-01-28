/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:18:26 by abausa-v          #+#    #+#             */
/*   Updated: 2024/03/06 19:18:31 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countdigits(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*stritoa;
	int		digits;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	digits = countdigits(n);
	stritoa = (char *)malloc((digits + 1) * sizeof(char));
	if (!stritoa)
		return (NULL);
	if (n == 0)
		stritoa[0] = '0';
	if (n < 0)
	{
		stritoa[0] = '-';
		n *= -1;
	}
	stritoa[digits] = '\0';
	digits--;
	while (digits >= 0 && n != 0)
	{
		stritoa[digits] = (n % 10) + '0';
		digits--;
		n /= 10;
	}
	return (stritoa);
}
