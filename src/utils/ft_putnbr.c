/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubretec <hubretec@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:13:24 by hubretec          #+#    #+#             */
/*   Updated: 2022/03/15 17:47:28 by hubretec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int nb)
{
	char			digit;
	unsigned int	nbr;

	if (nb < 0)
	{
		nbr = nb * -1;
		write(1, "-", 1);
	}
	else
		nbr = nb;
	if (nbr / 10)
		ft_putnbr(nbr / 10);
	digit = nbr % 10 + 48;
	write(1, &digit, 1);
}
