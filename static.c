/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:05:36 by                   #+#    #+#             */
/*   Updated: 2018/08/08 15:41:04 by ttshivhu         ###   ########.fr       */
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

void		static_otool(char *filen, unsigned char *addr, size_t size)
{
	struct fat_header *fat;
	struct mach_header_64 *header;
	struct segment_command *seg;
    char    *segd;

	header = (struct mach_header_64 *)addr;
	if (header->magic == MH_MAGIC_64)
		printf("no: %d\n", header->ncmds);
	seg = addr + (sizeof(struct mach_header_64 *) + sizeof(struct segment_command *));
	printf("segment: %d\n", seg->cmdsize);
    segd = addr + seg->fileoff;
    int i = 0;
    while (i < 100)
    {
        if (strcmp(segd, "__text") == 0)
            printf("found\n");
        segd++;
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
