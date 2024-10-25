/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base16 (1).c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:19:36 by sait-alo          #+#    #+#             */
/*   Updated: 2024/10/25 01:22:05 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_base16(unsigned long nb, char *base)
{
	int	printed;

	printed = 0;
	if (nb >= 16)
	{
		printed += ft_base16(nb / 16, base);
		printed += ft_base16(nb % 16, base);
	}
	else
		printed += ft_putchar(base[nb]);
	return (printed);
}
