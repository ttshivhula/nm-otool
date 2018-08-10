/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm32bit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 15:13:35 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/10 15:47:47 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theader.h"


void		sect(t_sections **head, struct segment_command *seg, int n)
{

	struct section *sect;
	static int j = 1;

	sect = (struct section *)&seg[1];
	int i = 0;
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
	char		*symname;
	struct nlist	*nl;
	int		i;

	i = -1;
	while (++i < nsyms)
	{
		nl = (struct nlist *)&symtab[i];
		symname = &names[nl->n_un.n_strx];
		if (!(nl->n_type & N_STAB))
		{
			ft_puthexa((long)nl->n_value, 8);
			ft_putchar(' ');
			print_symbol(s, nl->n_sect, nl->n_type);
			ft_putchar(' ');
			ft_putendl(symname);
		}
	}
}

void		nm_32(char *fname, unsigned char *addr)
{
	struct mach_header		*header;
	struct load_command		*load;
	struct symtab_command		*sym;
	struct segment_command		*seg = NULL;
	struct nlist			*symtab;
	t_sections			*shead = NULL;
	char				*names;
	int				i;

	header = (struct mach_header *)addr;
	load = (struct load_command *)&header[1];
	i = 0;
	while (i < header->ncmds)
	{
		if (load->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)load;
		}
		if (load->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command *)load;
			sect(&shead, seg, seg->nsects);
		}
		i++;
		load = (struct load_command*) ((char*)load + load->cmdsize);
	}
	symtab = (struct nlist *)((char *)addr + sym->symoff);
	i = 0;
	names = (char *)addr + sym->stroff;
	print_32(shead, symtab, names, sym->nsyms);
}
