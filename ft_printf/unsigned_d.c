/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 09:46:51 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/08/13 11:29:31 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		handle_neg(t_fmt *f, t_vars *v)
{
	v->df += ((f->width) ? (f->width - v->len) : f->prec - v->len);
	(f->prec || f->zero) ? ft_putnchar('0', v->df) : ft_putnchar(' ', v->df);
}

static void		length(t_vars *v, va_list ap, t_fmt *f, t_bools *b)
{
	if (f->z || f->l || f->ll || f->j)
		v->i = va_arg(ap, unsigned long long);
	else if (f->h)
		v->i = (unsigned short int)va_arg(ap, int);
	else if (f->hh)
		v->i = (unsigned char)va_arg(ap, int);
	else
		v->i = va_arg(ap, unsigned int);
	v->len = lenbase(v->i, 10);
	v->df = 0;
	b->n = 0;
	b->sp = 0;
	b->s = 0;
}

static void		blength(t_vars *v, va_list ap, t_fmt *f, t_bools *b)
{
	(void)f;
	v->i = va_arg(ap, long);
	v->len = lenbase(v->i, 10);
	v->df = 0;
	b->n = 0;
	b->sp = 0;
	b->s = 0;
}

static int		kill_lines(t_vars *v, t_fmt *f, t_bools *b)
{
	if ((f->width > v->len || f->prec > v->len) && f->left)
	{
		v->df = (f->width) ? f->width - v->len : f->prec - v->len;
		ft_putnchar(' ', v->df);
	}
	if (v->df)
	{
		if (b->s)
			return (((f->width) ? f->width + 1 + b->sp : f->prec + 1 + b->sp));
		else
			return ((f->width) ? f->width + b->sp : f->prec + b->sp);
	}
	return (v->len + b->sp);
}

int				unsigned_d(t_vars v, va_list ap, t_fmt *f)
{
	t_bools b;

	boolclean(&b);
	(!f->wide) ? length(&v, ap, f, &b) : blength(&v, ap, f, &b);
	if ((f->width > v.len || f->prec > v.len) && !f->left)
		handle_neg(f, &v);
	ft_putstr(ft_itoa_base(v.i, 10));
	return (kill_lines(&v, f, &b));
}
