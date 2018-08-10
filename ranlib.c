/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranlib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 11:17:18 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/10 14:06:49 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <mach-o/nlist.h>
#include <mach-o/loader.h>
#include <mach-o/stab.h>
#include <mach-o/ranlib.h>
#include <ar.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

typedef	struct			s_ranlibs
{
	void			*ptr;
	struct s_ranlibs	*next;
}				t_ranlibs;

int		map_file(char *filename, void **content,
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

void		add_objs(t_ranlibs **head, void *ptr)
{
	t_ranlibs *current;

	current = *head;
	if (*head == NULL)
	{
		*head = (t_ranlibs *)malloc(sizeof(t_ranlibs));
		(*head)->ptr = ptr;
		(*head)->next = NULL;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = (t_ranlibs *)malloc(sizeof(t_ranlibs));
		current->next->ptr = ptr;
		current->next->next = NULL;
	}
}

unsigned char	*ranlib_frame(void *ptr)
{
	unsigned char *file;
	size_t		i;

	i = 0;
	file = (unsigned char *)ptr;
	while (42)
	{
		if (file[i] == 0xcf && file[i + 1] == 0xfa)
			break ;
		if (file[i] == 0xce && file[i + 1] == 0xfa)
			break ;
		i++;
	}
	return (&file[i]);
}

void		print_sectsym(t_ranlibs * head)
{
	t_ranlibs	*current;
	struct mach_header_64 *header64;
	int	i;
	unsigned char	*tmp;
	
	current = head;
	while (current != NULL)
	{
		ft_putendl((char *)current->ptr);
			// nm or otool /
		tmp = ranlib_frame(current->ptr);
		header64 = (struct mach_header_64 *)tmp;
		printf("and it's 64 bit see? lookie here -> %llx\n", 
		       header64->magic);
		current = current->next;
	}
}

void		run_otool(void *file, int size)
{
	struct ranlib *ran32;
	struct ranlib_64 *ran64;
	struct mach_header_64 *header64;
	t_ranlibs *head = NULL;
	unsigned char	*ptr;

	ptr = (unsigned char *)file;
	if (ft_strncmp((char *)ptr, ARMAG, SARMAG) == 0)
		ft_putendl("ranlib format");
	int i = 0;
	int found = 1;
	while (i < size)
	{
		if (ptr[i] == '\n' && ptr[i - 1] == '`')
		{
			if (ft_strcmp((char *)ptr + i + 1, "__.SYMDEF SORTED"))
				add_objs(&head, (unsigned char *)file + i + 1);
		}
		i++;
	}
	print_sectsym(head);
}

int		main(int argc, char **argv)
{
	int	i;
	void	*content;
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
