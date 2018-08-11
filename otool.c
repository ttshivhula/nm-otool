/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 09:39:06 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/11 10:17:43 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theader.h"

void		print_first_part(unsigned long long addr, int start, int bits)
{
	char	*str;
	int	len;
	int	i;

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

void		print_other_hex(unsigned long long addr, int zero, int bits)
{
	char	*str;

	if (zero)
		write(1, "0", 1);
	str = ft_itoa_base(addr, 16);
	write(1, str, strlen(str));
	(str) ? free(str) : 0;
	write(1, " ", 1);
}

void		print_section(size_t addr, size_t size, unsigned char *file,
			      int bits)
{
	size_t		i;
	size_t		val;
	unsigned char	*content;
	int		is_16;

	val = addr;
	is_16 = 0;
	content = file;
	write(1, "Contents of (__TEXT,__text) section\n", 37);
	print_first_part(val, 1, bits);
	i = 0;
	while (i < size)
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
		i++;
		val++;
		is_16++;
	}
	ft_putchar('\n');
}

void		otool_64(char *fn, unsigned char *content)
{
	unsigned char	*file;
	struct section_64	*sect;

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
	size_t	start_addr = sect->addr;
	size_t	size = sect->size;
	size_t	start = sect->offset;
	print_section(start_addr, size, content + start, 16);
}

void		otool_32(char *fn, unsigned char *content)
{
	unsigned char	*file;
	struct section	*sect;

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
	size_t	start_addr = sect->addr;
	size_t	size = sect->size;
	size_t	start = sect->offset;
	print_section(start_addr, size, content + start, 8);
}

void		otool(char *fn, unsigned char *addr, int size)
{
	t_ranlibs *ranlibs;

	ranlibs = NULL;
	if (part_type(addr) == 1)
		add_ranlib(fn, addr, size, 0);
	else if (part_type(addr) == 2)
		otool_64(fn, addr);
	else if (part_type(addr) == 3)
		otool_32(fn, addr);
	else
	{
		ft_putstr(fn);
		ft_putendl(" The file was not recognized as a valid object file");
	}
}
