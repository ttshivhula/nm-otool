

#include <mach-o/nlist.h>
#include <mach-o/loader.h>
#include <mach-o/stab.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int		is_32_or_64(struct mach_header *head)
{
	if (head->magic == MH_MAGIC_64)
		return (1);
	return (0);
}

struct symtab_command		*segment_search(struct mach_header_64 *header,
		int ncmds, struct load_command *comm)
{
	struct symtab_command	*sym;
	int			i;

	i = 0;
	while (i < ncmds)
	{
		if (comm->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)comm;
			break ;
		}
		comm = (struct load_command *)((void*)comm +
			comm->cmdsize);
		i++;
	}
	return (sym);
}

void		print_labels(struct symtab_command *sym,
			unsigned char *content)
{
	struct nlist_64 *info;
	int		i;
	struct nlist_64 *another;
	char		*name;

	name = (char *)content + sym->stroff;
	info = (struct nlist_64 *)((void *)info + sym->symoff);
	i = 0;
	while (i < sym->nsyms)
	{
		another = &info[i];
		printf("%s :", &name[another->n_un.n_strx]);
		if (info->n_type & N_SECT)
			printf(" T ");
		printf("%x\n ", another->n_value);
		i++;
	}
}

void		nm64(struct mach_header *head, unsigned char *content)
{
	struct mach_header_64 *head64;
	struct load_command *stuff;
	int			delim;
	struct symtab_command *sym;

	head64 = (struct mach_header_64 *)head;
	stuff = (struct load_command *)&head64[1];
	delim = head64->ncmds;
	sym = segment_search(head64, delim, stuff);
	print_labels(sym, content);

}


void		nm32(struct mach_header *head)
{
	return ;
}

void		run_otool(unsigned char *content, size_t size)
{
	struct mach_header	*header;
	int			is_32;

	header = (struct mach_header *)content;
	is_32 = is_32_or_64(header);
	if (is_32 == 1)
		nm64(header, content);
	else
		nm32(header);
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
	return (1);
}

int		main(int argc, char **argv)
{
	int	i;
	unsigned char	*content;
	size_t			size;

	i = 1;
	while (i < argc)
	{
		map_file(argv[i], &content, &size);
		run_otool(content, size);
		i++;
	}
	return (0);
}
