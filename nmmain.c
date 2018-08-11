/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmmain.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 09:56:58 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/08/11 09:57:24 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "theader.h"

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
