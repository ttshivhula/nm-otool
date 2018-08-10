/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 14:18:12 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/10 15:47:39 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theader.h"

int		map_file(char *filename, unsigned char **content,
			 size_t *size)
{
	int		fd;
	struct stat	info;

	fd = open(filename, O_RDONLY);
	fstat(fd, &info);
	*size = info.st_size;
	*content = mmap(0, *size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (*content != NULL)
		return (1);
	return (0);
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

char	sect_char(char *sect, char *seg, int n_type)
{
	char	c;
	if (!strcmp(sect, "__common") && !strcmp(seg, "__DATA"))
		c = 's';
	if (!strcmp(sect, "__text"))
		c = 't';
	if (!strcmp(sect, "__bss"))
		c = 'b';
	if (!strcmp(sect, "__const"))
		c = 's';
	if (!strcmp(sect, "__data"))
		c = 'd';
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

void		print_symbol(t_sections * head, int index, int n_type)
{
	t_sections	*current;
	char		c;
	int		i;

	i = 1;
	c = 0;
	current = head;
	while (current != NULL)
	{
		if (i == index)
		{
			c = sect_char(current->sectname, current->segname, n_type);
			ft_putchar(c);
			return ;
		}
		current = current->next;
		i++;
	}
	if (n_type & N_ABS)
		c = 'a';
	if (n_type & N_INDR)
		c = 'i';
	c = c ? c : 'u';
	ft_putchar((n_type & N_EXT) ? c - 32 : c);
}
