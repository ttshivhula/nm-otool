/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 11:52:11 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/08/13 11:53:47 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		handle_neg(t_fmt *f, t_vars *v, t_bools *b)
{
	if (f->hash && (f->zero && f->prec))
	{
		ft_putchar('0');
		b->h = 1;
	}
	else if (f->hash && (!f->zero && !f->prec))
	{
		ft_putchar('0');
		b->h = 1;
		b->after = 1;
	}
	else if (f->hash)
	{
		b->h = 1;
		ft_putchar('0');
	}
	if (!f->left)
	{
		v->df += ((f->width) ? f->width - v->len : f->prec - v->len) - b->h;
		(f->prec || f->zero) ? ft_cn('0', v->df) : ft_cn(' ', v->df);
		(b->after) ? ft_putchar('0') : 0;
	}
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
	v->len = lenbase(v->i, 8);
	v->df = 0;
	b->sp = 0;
}

static void		blength(t_vars *v, va_list ap, t_fmt *f, t_bools *b)
{
	(void)f;
	v->i = va_arg(ap, unsigned long);
	v->len = lenbase(v->i, 8);
	v->df = 0;
	b->sp = 0;
}

static int		kill_lines(t_vars *v, t_fmt *f, t_bools *b)
{
	if ((f->width > v->len || f->prec > v->len) && f->left)
	{
		v->df = ((f->width) ? f->width - v->len : f->prec - v->len) - b->h;
		ft_putnchar(' ', v->df);
	}
	if (v->df)
	{
		return ((f->width) ? f->width + b->sp : f->prec + b->sp);
	}
	return (v->len + b->sp + b->special);
}

int				handle_o(t_vars v, va_list ap, t_fmt *f)
{
	t_bools b;

	boolclean(&b);
	(!f->wide) ? length(&v, ap, f, &b) : blength(&v, ap, f, &b);
	if (f->space && !f->sign && !(v.i < 0))
	{
		ft_putchar(' ');
		b.sp++;
	}
	if ((f->width > v.len || f->prec > v.len))
		handle_neg(f, &v, &b);
	else if (f->hash)
	{
		b.special = 1;
		ft_putchar('0');
	}
	ft_putstr(ft_itoa_base(v.i, 8));
	return (kill_lines(&v, f, &b));
}
