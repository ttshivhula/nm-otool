/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 09:53:46 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/11 10:51:17 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theader.h"

int		len_base(long long nb, int base)
{
	int				len;

	len = 0;
	if (nb < 0)
	{
		nb = -nb;
		if (base == 10)
			len++;
	}
	len++;
	nb /= base;
	while (nb)
	{
		len++;
		nb /= base;
	}
	return (len);
}

char	*ft_itoa_base(long long n, int base)
{
	char			*ret;
	int				s;
	int				i;

	i = len_base(n, base);
	s = 0;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	ret[i--] = '\0';
	if (n < 0)
	{
		n = -n;
		(base == 10) ? s = 1 : 0;
	}
	ret[i--] = (n % base < 10) ? (n % base) + 48 : (n % base) + 87;
	n /= base;
	while (i >= 0)
	{
		if (i == 0 && s == 1)
			ret[i--] = '-';
		ret[i--] = (n % base < 10) ? (n % base) + 48 : (n % base) + 87;
		n /= base;
	}
	return (ret);
}

void	print_first_part(unsigned long long addr, int start, int bits)
{
	char	*str;
	int		len;
	int		i;

	if (!start)
		write(1, "\n", 1);
	str = ft_itoa_base(addr, bits);
	len = ft_strlen(str);
	i = 0;
	while (i < bits - len)
	{
		write(1, "0", 1);
		i++;
	}
	write(1, str, len);
	(str) ? free(str) : 0;
	write(1, "\t", 1);
}
