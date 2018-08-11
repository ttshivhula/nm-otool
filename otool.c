/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 09:39:06 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/11 15:03:09 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theader.h"

void		print_other_hex(unsigned long long addr, int zero, int bits)
{
	char	*str;

	if (zero)
		write(1, "0", 1);
	str = ft_itoa_base(addr, 16);
	write(1, str, strlen(str));
	(str) ? free(str) : 0;
	write(1, " ", 1);
	(void)bits;
}

void		print_section(size_t addr, size_t size, unsigned char *content,
		int bits)
{
	size_t				i;
	size_t				val;
	int					is_16;

	val = addr;
	is_16 = 0;
	ft_putendl("Contents of (__TEXT,__text) section");
	size ? print_first_part(val, 1, bits) : 0;
	i = -1;
	while (++i < size)
	{
		if (is_16 % 16 == 0 && is_16 != 0)
		{
			print_first_part(val, 0, bits);
			is_16 = 0;
		}
		if (content[i] < 16 && content[i] > 0)
			print_other_hex(content[i], 1, bits);
		else if (content[i] == 0)
			write(1, "00 ", 3);
		else
			print_other_hex(content[i], 0, bits);
		val++;
		is_16++;
	}
}

void		otool_64(char *fn, unsigned char *content)
{
	unsigned char		*file;
	struct section_64	*sect;

	if (fn)
	{
		ft_putstr(fn);
		ft_putendl(":");
	}
	file = (unsigned char *)content;
	while (42)
	{
		if (strcmp((const char*)file, "__text") == 0)
		{
			sect = (struct section_64 *)file;
			break ;
		}
		file++;
	}
	print_section(sect->addr, sect->size, content + sect->offset, 16);
	ft_putchar('\n');
}

void		otool_32(char *fn, unsigned char *content)
{
	unsigned char	*file;
	struct section	*sect;

	if (fn)
	{
		ft_putstr(fn);
		ft_putendl(":");
	}
	file = (unsigned char *)content;
	while (42)
	{
		if (ft_strcmp((const char*)file, "__text") == 0)
		{
			sect = (struct section *)file;
			break ;
		}
		file++;
	}
	print_section(sect->addr, sect->size, content + sect->offset, 8);
	ft_putchar('\n');
}

void		otool(char *fn, unsigned char *addr, int size)
{
	t_ranlibs	*ranlibs;
	int			offset;

	offset = 0;
	ranlibs = NULL;
	if (part_type(addr, size, &offset) == 1)
		add_ranlib(fn, addr + offset, size, 0);
	else if (part_type(addr, size, &offset) == 2)
		otool_64(fn, addr + offset);
	else if (part_type(addr, size, &offset) == 3)
		otool_32(fn, addr + offset);
	else
	{
		ft_putstr(fn);
		ft_putendl(" The file was not recognized as a valid object file");
	}
}
