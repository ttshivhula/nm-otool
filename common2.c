/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 14:27:57 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/11 13:04:39 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theader.h"

int			map_file(char *filename, unsigned char **content,
		size_t *size)
{
	int			fd;
	struct stat	info;

	fd = open(filename, O_RDONLY);
	fstat(fd, &info);
	if (fd == -1 || S_ISDIR(info.st_mode))
	{
		ft_putstr(filename);
		ft_putendl(" No such file or directory.");
		return (0);
	}
	*size = info.st_size;
	*content = mmap(0, *size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (*content != NULL)
		return (1);
	return (0);
}

int			part_type(unsigned char *addr)
{
	struct mach_header_64	*h64;
	struct mach_header		*h32;

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

void		add_sect(t_sections **head, char *sect, char *seg)
{
	t_sections *current;

	current = *head;
	if (*head == NULL)
	{
		*head = (t_sections *)malloc(sizeof(t_sections));
		(*head)->sectname = sect;
		(*head)->segname = seg;
		(*head)->next = NULL;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = (t_sections *)malloc(sizeof(t_sections));
		current->next->sectname = sect;
		current->next->segname = seg;
		current->next->next = NULL;
	}
}
