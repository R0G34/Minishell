/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:20:29 by abausa-v          #+#    #+#             */
/*   Updated: 2024/03/06 19:20:33 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex_low(unsigned long long h, int printcount)
{
	char	*hexlow;

	hexlow = "0123456789abcdef";
	if (h < 16)
		printcount = ft_putchar_mod(hexlow[h], printcount);
	else
	{
		printcount = ft_puthex_low(h / 16, printcount);
		printcount = ft_puthex_low(h % 16, printcount);
	}
	return (printcount);
}

int	ft_puthex_upp(unsigned long long h, int printcount)
{
	char	*hexupp;

	hexupp = "0123456789ABCDEF";
	if (h < 16)
		printcount = ft_putchar_mod(hexupp[h], printcount);
	else
	{
		printcount = ft_puthex_upp(h / 16, printcount);
		printcount = ft_puthex_upp(h % 16, printcount);
	}
	return (printcount);
}

int	ft_putptr(void *ptr, int printcount)
{
	printcount = ft_putstr_mod("0x", printcount);
	printcount = ft_puthex_low((unsigned long)ptr, printcount);
	return (printcount);
}

int	ft_putnbr_mod(int nb, int printcount)
{
	long	nb_aux;
	char	digit;

	nb_aux = nb;
	if (nb_aux < 0)
	{
		write(1, "-", 1);
		printcount++;
		nb_aux = -nb_aux;
	}
	if (nb_aux >= 10)
		printcount = ft_putnbr_mod(nb_aux / 10, printcount);
	digit = nb_aux % 10 + 48;
	write(1, &digit, 1);
	printcount++;
	return (printcount);
}

int	ft_putnbr_mod_unsigned(unsigned int nb, int printcount)
{
	long	nb_aux;
	char	digit;

	nb_aux = nb;
	if (nb_aux >= 10)
		printcount = ft_putnbr_mod(nb_aux / 10, printcount);
	digit = nb_aux % 10 + 48;
	write(1, &digit, 1);
	printcount++;
	return (printcount);
}
