/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:05:36 by                   #+#    #+#             */
/*   Updated: 2018/08/09 17:14:31 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>

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
/*
 * TODO: identify all the sections
*/

void		sections(struct segment_command_64 *seg, int n)
{

	struct section_64 *sect;

	sect = (struct section_64 *)seg;
	int i = 0;
	printf("no segs: %d\n", n);
	while (i < n)
	{
		printf("segment name: %s\n", sect->sectname);
		sect = (struct section_64 *)((char *)sect + sect->size);
		i++;
	}
}
void		static_otool(char *filen, unsigned char *addr, size_t size)
{
	struct fat_header *fat;
	struct mach_header_64 *header;
	struct load_command *load;
	struct symtab_command *sym;
	struct segment_command_64 * seg = NULL;

	header = (struct mach_header_64 *)addr;
	load = (struct load_command *)&header[1];
	int i = 0;
	while (i < header->ncmds)
	{
		if (load->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)load;
		}
		if (load->cmd == LC_SEGMENT_64 && !seg)
		{
			//printf("lc seg found\n");
			seg = (struct segment_command_64 *)load;
			sections(seg, seg->nsects);
			//break ;
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
			printf("s:   %s sect: %d type: %d val: %llx\n", symname,
			       nl->n_sect, nl->n_type & N_EXT, nl->n_value);
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
			static_otool(argv[i], content, size);
		i++;
	}
	return (0);
}
