/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranlib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 11:17:18 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/11 10:29:46 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theader.h"

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

void		run_nm(char *fn, t_ranlibs * head, int size)
{
	t_ranlibs	*current;
	unsigned char	*tmp;
	char		*name;
	
	current = head;
	while (current != NULL)
	{
		tmp = ranlib_frame(current->ptr);
		ft_putstr(fn);
		ft_putchar('(');
		ft_putstr(current->ptr);
		ft_putendl("):");
		nm(fn, tmp, size);
		if (current->next)
			ft_putchar('\n');
		current = current->next;
	}
}

void		run_otool(char *fn, t_ranlibs * head, int size)
{
	t_ranlibs	*current;
	unsigned char	*tmp;
	char		*name;
	
	current = head;
	while (current != NULL)
	{
		tmp = ranlib_frame(current->ptr);
		ft_putstr(fn);
		ft_putchar('(');
		ft_putstr(current->ptr);
		ft_putendl("):");
		otool(NULL, tmp, size);
		current = current->next;
	}
}
void		add_ranlib(char *fn, unsigned char *ptr, int size, int prog)
{
	t_ranlibs	*head;
	int		i;

	i = 0;
	head = NULL;
	while (i < size)
	{
		if (ptr[i] == '\n' && ptr[i - 1] == '`')
		{
			if (ft_strcmp((char *)ptr + i + 1, "__.SYMDEF SORTED"))
				add_objs(&head, (unsigned char *)ptr + i + 1);
		}
		i++;
	}
	if (prog)
		run_nm(fn, head, size);
	else
		run_otool(fn, head, size);
}
