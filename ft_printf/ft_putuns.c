/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:01:55 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/10/04 23:08:28 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	cont_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int	ft_putuns(unsigned int nbr)
{
	int	len;

	len = cont_len(nbr);
	if (nbr > 9)
	{
		ft_putuns(nbr / 10);
		ft_putuns(nbr % 10);
	}
	else
		ft_putchar(nbr + '0');
	return (len);
}
