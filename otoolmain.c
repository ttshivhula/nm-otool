/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otoolmain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 09:50:58 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/13 08:58:28 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theader.h"

int		main(int argc, char **argv)
{
	int				i;
	unsigned char	*content;
	size_t			size;

	i = 1;
	while (i < argc)
	{
		if (map_file(argv[i], &content, &size))
		{
			otool(argv[i], content, size);
			munmap(content, size);
		}
		i++;
	}
	return (0);
}
