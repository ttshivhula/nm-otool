/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 14:27:57 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/10 16:18:54 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theader.h"

int		part_type(unsigned char *addr)
{
	struct mach_header_64	*h64;
	struct mach_header	*h32;

	if (!ft_strncmp((char *)addr, ARMAG, SARMAG))
		return (1);
	h64 = (struct mach_header_64 *)addr;
	h32 = (struct mach_header *)addr;
	if (h64->magic == MH_MAGIC_64 || h64->magic == MH_CIGAM_64)
		return (2);
	if (h32->magic == MH_MAGIC || h32->magic == MH_CIGAM)
		return (3);
	return (0);
}

void		padding(long long n, int def, int bits)
{
	int i;

	i = -1;
	if (!(def == 'u' || def == 'U') && !n)
	{
		while (++i < bits)
			ft_putchar('0');
	}
	else
		ft_puthexa(n, bits);
}
