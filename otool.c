#include <mach-o/nlist.h>
#include <mach-o/loader.h>
#include <mach-o/stab.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft/libft.h"

int					len_base(long long nb, int base)
{
	int				len;

	len = 0;
	if (nb < 0)
	{
		nb = -nb;
		if (base == 10)
			len++;
	}
	len++;
	nb /= base;
	while (nb)
	{
		len++;
		nb /= base;
	}
	return (len);
}

char				*ft_itoa_base(long long n, int base)
{
	char			*ret;
	int				s;
	int				i;

	i = len_base(n, base);
	s = 0;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	ret[i--] = '\0';
	if (n < 0)
	{
		n = -n;
		(base == 10) ? s = 1 : 0;
	}
	ret[i--] = (n % base < 10) ? (n % base) + 48 : (n % base) + 87;
	n /= base;
	while (i >= 0)
	{
		if (i == 0 && s == 1)
			ret[i--] = '-';
		ret[i--] = (n % base < 10) ? (n % base) + 48 : (n % base) + 87;
		n /= base;
	}
	return (ret);
}

int		is_32_or_64(struct mach_header *head)
{
	if (head->magic == MH_MAGIC_64)
		return (1);
	return (0);
}

void		print_first_part(unsigned long long addr, int start)
{
	char	*str;
	int	len;
	int	i;

	if (!start)
		write(1, "\n", 1);
	str = ft_itoa_base(addr, 16);
	len = ft_strlen(str);
	i = 0;
	while (i < 16 - len)
	{
		if (i != 8)
			write(1, "0", 1);
		else
			write(1, "1", 1);
		i++;
	}
	write(1, str, len);
	write(1, "\t", 1);
}

void		print_other_hex(unsigned long long addr, int zero)
{
	char	*str;

	if (zero)
		write(1, "0", 1);
	str = ft_itoa_base(addr, 16);
	write(1, str, strlen(str));
	write(1, " ", 1);
}

void		print_section_64(size_t addr, size_t size, size_t start,
				 unsigned char *file)
{
	size_t		i;
	size_t		val;
	unsigned char	*content;
	int		is_16;

	val = addr;
	is_16 = 0;
	content = file + start;
	write(1, "\nContents of (__TEXT,__text) section\n", 37);
	print_first_part(val, 1);
	i = 0;
	while (i < size)
	{
		if (is_16 % 16 == 0 && is_16 != 0)
		{
			print_first_part(val, 0);
			is_16 = 0;
		}
		if (content[i] < 16 && content[i] > 0)
			print_other_hex(content[i], 1);
		else if (content[i] == 0)
			write(1, "00 ", 3);
		else
			print_other_hex(content[i], 0);
		i++;
		val++;
		is_16++;
	}
	write(1, "\n", 1);
}

void		find_text_section_64(struct mach_header_64 *head64,
			unsigned char *content)
{
	unsigned char	*file;
	struct section_64	*sect;

	file = (unsigned char *)&head64[1];
	while (42)
	{
		if (strcmp((const char*)file, "__text") == 0)
		{
			sect = (struct section_64 *)file;
			break ;
		}
		file++;
	}
	size_t	start_addr = sect->addr;
	size_t	size = sect->size;
	size_t	start = sect->offset;
	print_section_64(start_addr, size, start, content);
}

void		find_text_section_32(struct mach_header *head,
			unsigned char *content)
{
	unsigned char	*file;
	struct section	*sect;

	file = (unsigned char *)&head[1];
	while (42)
	{
		if (ft_strcmp((const char*)file, "__text") == 0)
		{
			sect = (struct section *)file;
			break ;
		}
		file++;
	}
	size_t	start_addr = sect->addr;
	size_t	size = sect->size;
	size_t	start = sect->offset;
	print_section_64(start_addr, size, start, content);
}

void		otool64(struct mach_header *head, unsigned char *content)
{
	struct mach_header_64 *head64;

	head64 = (struct mach_header_64 *)head;
	find_text_section_64(head64, content);
}


void		run_otool(char *fname, unsigned char *content, size_t size)
{
	struct mach_header	*header;
	int			is_32;

	write(1, fname, ft_strlen(fname));
	write(1, ":", 1);
	header = (struct mach_header *)content;
	is_32 = is_32_or_64(header);
	if (is_32 == 1)
		otool64(header, content);
	else
		find_text_section_32(header, content);
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
			run_otool(argv[i], content, size);
		i++;
	}
	return (0);
}
