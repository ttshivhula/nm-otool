/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 09:26:21 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/08/13 11:49:51 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_wlen(wchar_t wc)
{
	unsigned int i;

	i = (unsigned int)wc;
	if (i <= 127)
		return (1);
	else if (i <= 2047)
		return (2);
	else if (i <= 65535)
		return (3);
	else
		return (4);
}

void	ft_cn(char c, int n)
{
	ft_putnchar(c, n);
}

int		ft_wstrlen(wchar_t *ws)
{
	int len;

	len = 0;
	while (*ws)
	{
		len += ft_wlen(*ws);
		ws++;
	}
	return (len);
}

int		ft_putwstr(wchar_t *ws)
{
	int len;

	if (!ws)
		return (ft_printf("(null)"));
	len = 0;
	while (*ws)
	{
		len += ft_putwchar(*ws);
		ws++;
	}
	return (len);
}

void	neg_line_kill(t_fmt *f, t_vars *v, t_bools *b)
{
	if (v->i < 0)
	{
		b->n = 1;
		if (f->prec || f->zero)
		{
			v->i = -(v->i);
			ft_putchar('-');
			if (f->prec)
			{
				v->df++;
				b->s = 1;
			}
		}
	}
}
