/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theader.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 14:13:32 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/10 16:36:57 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _THEADER_H_
# define _THEADER_H_

# include "libft/libft.h"
# include <mach-o/nlist.h>
# include <mach-o/loader.h>
# include <mach-o/stab.h>
# include <mach-o/ranlib.h>
# include <ar.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef	struct			s_ranlibs
{
	void			*ptr;
	struct s_ranlibs	*next;
}				t_ranlibs;

typedef		struct		s_sections
{
	char			*sectname;
	char			*segname;
	struct			s_sections *next;
}				t_sections;

int		map_file(char *filename, unsigned char **content, size_t *size);
void		add_sect(t_sections **head, char *sect, char *seg);
char		sect_char(char *sect, char *seg, int n_type);
void		ft_putnchar(char c, int n);
void		ft_puthexa(long long nb, int bits);
char		get_symbol(t_sections * head, int index, int n_type);
void		nm_32(char *fname, unsigned char *addr);
void		nm(char *fn, unsigned char *addr, int size);
int		part_type(unsigned char *addr);
void		padding(long long n, int def, int bits);
void		add_ranlib(char *fn, unsigned char *ptr, int size, int prog);

#endif