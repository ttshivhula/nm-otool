/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmmain.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 09:56:58 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/11 15:26:35 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theader.h"

int		main(int argc, char **argv)
{
	int				i;
	unsigned char	*content;
	size_t			size;

	i = 1;
	content = NULL;
	while (i < argc)
	{
		if (argc > 2)
		{
			ft_putchar('\n');
			ft_putstr(argv[i]);
			ft_putendl(":");
		}
		if (map_file(argv[i], &content, &size))
			nm(argv[i], content, size);
		i++;
	}
	return (0);
}
