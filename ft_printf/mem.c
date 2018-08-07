/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 17:50:38 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/08/13 09:03:59 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		mem(int *ox, t_vars *v, t_fmt *f)
{
	f->width = (f->width) ? f->width + 2 : f->prec + 2;
	v->df = f->width - v->len;
	if (f->prec || f->zero)
	{
		*ox = 1;
		ft_putstr("0x");
		ft_putnchar('0', v->df);
	}
	else
		ft_putnchar(' ', v->df);
}

int				handle_p(t_vars v, va_list ap, t_fmt *f)
{
	int ox;

	ox = 0;
	v.ll = va_arg(ap, long long);
	v.len = v.ll ? lenbase(v.ll, 16) + 2 : 3;
	v.df = 0;
	if ((f->width > v.len || f->prec > v.len) && (!f->left))
		mem(&ox, &v, f);
	(!ox) ? ft_putstr("0x") : 0;
	ft_putstr(ft_itoa_base(v.ll, 16));
	if ((f->width > v.len || f->prec > v.len) && f->left)
	{
		v.df = (f->width) ? f->width - v.len : f->prec - v.len;
		ft_putnchar(' ', v.df);
	}
	if (v.df)
		return (f->width ? f->width : f->prec);
	return (v.len);
}
