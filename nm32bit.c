/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm32bit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 15:13:35 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/11 11:24:50 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theader.h"

void		sect(t_sections **head, struct segment_command *seg, int n)
{
	struct section	*sect;
	int				i;

	sect = (struct section *)&seg[1];
	i = 0;
	while (i < n)
	{
		add_sect(head, sect->sectname, sect->segname);
		sect = (struct section *)((char *)sect +
				sizeof(struct section));
		i++;
	}
}

void		print_32(t_sections *s, struct nlist *symtab, char *names,
		int nsyms)
{
	char			*symname;
	struct nlist	*nl;
	int				i;
	char			c;

	i = -1;
	while (++i < nsyms)
	{
		nl = (struct nlist *)&symtab[i];
		symname = &names[nl->n_un.n_strx];
		if (!(nl->n_type & N_STAB))
		{
			c = get_symbol(s, nl->n_sect, nl->n_value, nl->n_type);
			padding(nl->n_value, c, 8);
			ft_putchar(' ');
			ft_putchar(c);
			ft_putchar(' ');
			ft_putendl(symname);
		}
	}
	free_sections(s);
}

void		nm_32(char *fname, unsigned char *addr)
{
	t_structs		ts;
	int				i;

	ts.shead = NULL;
	ts.header = (struct mach_header *)addr;
	ts.load = (struct load_command *)&ts.header[1];
	i = 0;
	while (i < ts.header->ncmds)
	{
		if (ts.load->cmd == LC_SYMTAB)
		{
			ts.sym = (struct symtab_command *)ts.load;
		}
		if (ts.load->cmd == LC_SEGMENT)
		{
			ts.seg = (struct segment_command *)ts.load;
			sect(&ts.shead, ts.seg, ts.seg->nsects);
		}
		i++;
		ts.load = (struct load_command*)((char*)ts.load +
				ts.load->cmdsize);
	}
	ts.symtab = (struct nlist *)((char *)addr + ts.sym->symoff);
	print_32(ts.shead, ts.symtab, (char *)addr + ts.sym->stroff, ts.sym->nsyms);
}
