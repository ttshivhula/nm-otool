/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:05:36 by                   #+#    #+#             */
/*   Updated: 2018/08/10 14:23:31 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include "libft/libft.h"

/*typedef		struct s_sections
{
	char	*sectname;
	char	*segname;
	struct s_sections *next;
}			t_sections;

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
}*/

void		sections(t_sections **head, struct segment_command_64 *seg, int n)
{

	struct section_64 *sect;
	static int j = 1;

	sect = (struct section_64 *)&seg[1];
	int i = 0;
	while (i < n)
	{
		add_sect(head, sect->sectname, sect->segname);
		sect = (struct section_64 *)((char *)sect + sizeof(struct section_64));
		i++;
	}
}

/*char	sect_char(char *sect, char *seg, int n_type)
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

void		print_sectsym(t_sections * head, int index, int n_type)
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
}*/

void		static_nm(char *filen, unsigned char *addr, size_t size)
{
	struct mach_header_64 *header;
	struct load_command *load;
	struct symtab_command *sym;
	struct segment_command_64 * seg = NULL;
	t_sections *shead = NULL;

	header = (struct mach_header_64 *)addr;
	load = (struct load_command *)&header[1];
	int i = 0;
	while (i < header->ncmds)
	{
		if (load->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)load;
		}
		if (load->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)load;
			sections(&shead, seg, seg->nsects);
		}
		i++;
		load = (struct load_command*) ((char*)load + load->cmdsize);
	}
	struct nlist_64 *symtab = (struct nlist_64 *)((char *)addr + sym->symoff);
	i = 0;
	char	*names = (char *)addr + sym->stroff;
	while (i < sym->nsyms)
	{
		struct nlist_64 *nl =(struct nlist_64 *)&symtab[i];
		char	*symname = &names[nl->n_un.n_strx];
		if (!(nl->n_type & N_STAB))
		{
			//printf("%llx %s type: %d -- ", nl->n_value, symname, nl->n_type & N_EXT);
			ft_puthexa(nl->n_value, 16);
			ft_putchar(' ');
			//ft_putnbr(nl->n_sect);
			print_sectsym(shead, nl->n_sect, nl->n_type);
			ft_putchar(' ');
			ft_putendl(symname);
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	int	i;
	unsigned char	*content;
	size_t			size;

	i = 1;
	while (i < argc)
	{
		if (map_file(argv[i], &content, &size))
			static_nm(argv[i], content, size);
		i++;
	}
	return (0);
}
