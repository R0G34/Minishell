/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:20:55 by abausa-v          #+#    #+#             */
/*   Updated: 2024/03/06 19:20:58 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	long	nb_aux;
	char	digit;

	nb_aux = nb;
	if (nb_aux < 0)
	{
		write(fd, "-", 1);
		nb_aux = -nb_aux;
	}
	if (nb_aux < 10)
	{
		digit = nb_aux + 48;
		write(fd, &digit, 1);
	}
	if (nb_aux >= 10)
	{
		ft_putnbr_fd(nb_aux / 10, fd);
		digit = nb_aux % 10 + 48;
		write(fd, &digit, 1);
	}
}
