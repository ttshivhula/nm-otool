/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 14:18:12 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/11 12:02:05 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theader.h"

char	sect_char(char *sect, char *seg, int n_type)
{
	char	c;

	(void)seg;
	if (!strcmp(sect, "__text"))
		c = 't';
	else if (!strcmp(sect, "__bss"))
		c = 'b';
	else if (!strcmp(sect, "__data"))
		c = 'd';
	else
		c = 's';
	return ((n_type & N_EXT) ? c - 32 : c);
}

void	ft_putnchar(char c, int n)
{
	int i;

	i = -1;
	while (++i < n)
		ft_putchar(c);
}

void	ft_puthexa(long long nb, int bits)
{
	char	hex[255];
	int		i;

	i = 0;
	ft_bzero(hex, 255);
	nb ? 0 : ft_putnchar(' ', bits);
	while (nb)
	{
		if (nb % 16 >= 10)
			hex[i] = nb % 16 + 'a' - 10;
		else
			hex[i] = nb % 16 + '0';
		nb /= 16;
		i++;
	}
	i ? ft_putnchar('0', bits - i) : 0;
	while (i >= 0)
	{
		write(1, &hex[i], 1);
		i--;
	}
}

char	more_symbols(int addr, uint32_t type)
{
	char	ret;

	ret = '?';
	if ((type & N_TYPE) == N_UNDF)
	{
		if (addr)
			ret = 'c';
		else
			ret = 'u';
	}
	else if ((type & N_TYPE) == N_ABS)
		ret = 'a';
	else if ((type & N_TYPE) == N_PBUD)
		ret = 'u';
	else if ((type & N_TYPE) == N_INDR)
		ret = 'i';
	if ((type & N_STAB) != 0)
		ret = 'z';
	return (ret);
}

char	get_symbol(t_sections *head, int index, int addr, int n_type)
{
	t_sections		*current;
	char			c;
	int				i;

	i = 1;
	current = head;
	while (current != NULL)
	{
		if (i == index)
		{
			c = sect_char(current->sectname, current->segname, n_type);
			return (c);
		}
		current = current->next;
		i++;
	}
	c = more_symbols(addr, n_type);
	return ((n_type & N_EXT) ? c - 32 : c);
}
