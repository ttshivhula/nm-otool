/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 14:31:11 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/10 16:37:43 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theader.h"

void		sect_64(t_sections **head, struct segment_command_64 *seg, int n)
{

	struct section_64 *sect;
	static int j = 1;

	sect = (struct section_64 *)&seg[1];
	int i = 0;
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
	char		*symname;
	struct nlist_64	*nl;
	int		i;
	char		c;

	i = -1;
	while (++i < nsyms)
	{
		nl = (struct nlist_64 *)&symtab[i];
		symname = &names[nl->n_un.n_strx];
		if (!(nl->n_type & N_STAB))
		{
			c = get_symbol(s, nl->n_sect, nl->n_type);
			padding(nl->n_value, c, 16);
			ft_putchar(' ');
			ft_putchar(c);
			ft_putchar(' ');
			ft_putendl(symname);
		}
	}
}

void		nm_64(char *fname, unsigned char *addr)
{
	struct mach_header_64		*header;
	struct load_command		*load;
	struct symtab_command		*sym;
	struct segment_command_64	*seg = NULL;
	struct nlist_64			*symtab;
	t_sections			*shead = NULL;
	char				*names;
	int				i;

	header = (struct mach_header_64 *)addr;
	load = (struct load_command *)&header[1];
	i = 0;
	while (i < header->ncmds)
	{
		if (load->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)load;
		}
		if (load->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)load;
			sect_64(&shead, seg, seg->nsects);
		}
		i++;
		load = (struct load_command*) ((char*)load + load->cmdsize);
	}
	symtab = (struct nlist_64 *)((char *)addr + sym->symoff);
	i = 0;
	names = (char *)addr + sym->stroff;
	print_64(shead, symtab, names, sym->nsyms);
}

void		nm(char *fn, unsigned char *addr, int size)
{
	t_ranlibs *ranlibs;

	ranlibs = NULL;
	if (part_type(addr) == 1)
		add_ranlib(fn, addr, size, 1);
	else if (part_type(addr) == 2)
		nm_64(fn, addr);
	else if (part_type(addr) == 3)
		nm_32(fn, addr);
	else
	{
		ft_putstr(fn);
		ft_putendl(" The file was not recognized as a valid object file");
	}
}

int		main(int argc, char **argv)
{
	int	i;
	unsigned char	*content;
	size_t			size;

	i = 1;
	content = NULL;
	while (i < argc)
	{
		if (map_file(argv[i], &content, &size))
			nm(argv[i], content, size);
		i++;
	}
	return (0);
}
