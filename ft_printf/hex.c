/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 15:49:28 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/08/13 12:06:49 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		hexlength(t_vars *v, va_list ap, t_fmt *f)
{
	if (f->z || f->l || f->ll || f->j)
		v->i = va_arg(ap, unsigned long long);
	else if (f->h)
		v->i = (unsigned short int)va_arg(ap, int);
	else if (f->hh)
		v->i = (unsigned char)va_arg(ap, int);
	else
		v->i = va_arg(ap, unsigned int);
	v->len = lenbase(v->i, 16);
	v->df = 0;
}

static int		norm_fix(t_vars *v, t_fmt *f, int *ox)
{
	int i;

	i = (f->hash) ? -2 : 0;
	if (f->wide)
		ft_putstr(ft_itoa_base_cap(v->i, 16));
	else
		ft_putstr(ft_itoa_base(v->i, 16));
	if ((f->width > v->len || f->prec > v->len) && f->left)
	{
		v->df = ((f->width) ? f->width - v->len : f->prec - v->len) + i;
		ft_putnchar(' ', v->df);
		*ox = 0;
	}
	if (v->df)
		return (((f->width) ? f->width + *ox : f->prec + *ox));
	if (f->hash && v->i)
		return (v->len + *ox);
	return (v->len);
}

int				handle_hex(t_vars v, va_list ap, t_fmt *f)
{
	int ox;
	int pr;

	ox = 2;
	pr = 0;
	hexlength(&v, ap, f);
	if ((f->width > v.len || f->prec > v.len) && !f->left)
	{
		if (f->hash && (f->zero || f->prec) && v.i)
		{
			(f->wide) ? ft_putstr("0X") : ft_putstr("0x");
			pr = 1;
		}
		ox = 0;
		v.df += ((f->width) ? (f->width - v.len) : f->prec - v.len);
		v.df = (f->hash) ? v.df - 2 : v.df;
		(f->zero) ? ft_putnchar('0', v.df) : ft_putnchar(' ', v.df);
	}
	if (f->hash && !pr && v.i)
	{
		(f->wide) ? ft_putstr("0X") : ft_putstr("0x");
	}
	if (f->hash && f->prec && v.i == 0)
		return (0);
	return (norm_fix(&v, f, &ox));
}
