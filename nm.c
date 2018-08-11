/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 14:31:11 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/11 12:01:06 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theader.h"

void		sect_64(t_sections **head, struct segment_command_64 *seg, int n)
{
	struct section_64	*sect;
	int					i;

	sect = (struct section_64 *)&seg[1];
	i = 0;
	while (i < n)
	{
		add_sect(head, sect->sectname, sect->segname);
		sect = (struct section_64 *)((char *)sect +
				sizeof(struct section_64));
		i++;
	}
}

void		print_64(t_sections *s, struct nlist_64 *symtab, char *names,
		int nsyms)
{
	char			*symname;
	struct nlist_64	*nl;
	int				i;
	char			c;

	i = -1;
	while (++i < nsyms)
	{
		nl = (struct nlist_64 *)&symtab[i];
		symname = &names[nl->n_un.n_strx];
		if (!(nl->n_type & N_STAB))
		{
			c = get_symbol(s, nl->n_sect, nl->n_value, nl->n_type);
			padding(nl->n_value, c, 16);
			ft_putchar(' ');
			ft_putchar(c);
			ft_putchar(' ');
			ft_putendl(symname);
		}
	}
	free_sections(s);
}

void		nm_64(unsigned char *addr)
{
	t_structs64			ts;
	int					i;

	ts.shead = NULL;
	ts.header = (struct mach_header_64 *)addr;
	ts.load = (struct load_command *)&ts.header[1];
	i = 0;
	while (i < (int)ts.header->ncmds)
	{
		if (ts.load->cmd == LC_SYMTAB)
		{
			ts.sym = (struct symtab_command *)ts.load;
		}
		if (ts.load->cmd == LC_SEGMENT_64)
		{
			ts.seg = (struct segment_command_64 *)ts.load;
			sect_64(&ts.shead, ts.seg, ts.seg->nsects);
		}
		i++;
		ts.load = (struct load_command*)((char*)ts.load +
				ts.load->cmdsize);
	}
	ts.symtab = (struct nlist_64 *)((char *)addr + ts.sym->symoff);
	print_64(ts.shead, ts.symtab, (char *)addr + ts.sym->stroff, ts.sym->nsyms);
}

void		nm(char *fn, unsigned char *addr, int size)
{
	t_ranlibs *ranlibs;

	ranlibs = NULL;
	if (part_type(addr) == 1)
		add_ranlib(fn, addr, size, 1);
	else if (part_type(addr) == 2)
		nm_64(addr);
	else if (part_type(addr) == 3)
		nm_32(addr);
	else
	{
		ft_putstr(fn);
		ft_putendl(" The file was not recognized as a valid object file");
	}
}
