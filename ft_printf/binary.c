/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 08:18:42 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/08/13 10:54:49 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			asteric(t_fmt *f, char **fmt, va_list ap, int pos)
{
	int i;

	if (*(*fmt) == '*')
	{
		i = va_arg(ap, int);
		if (pos == 0)
		{
			f->width = (i < 0) ? -i : i;
			f->left = (i < 0) ? 1 : 0;
		}
		else
		{
			f->prec = (i < 0) ? -i : i;
		}
		(*fmt)++;
	}
}

static void		handle_neg(t_fmt *f, t_vars *v)
{
	v->df += ((f->width) ? (f->width - v->len) : f->prec - v->len);
	(f->prec || f->zero) ? ft_putnchar('0', v->df) : ft_putnchar(' ', v->df);
}

static void		blength(t_vars *v, va_list ap, t_fmt *f, t_bools *b)
{
	(void)f;
	v->i = va_arg(ap, long long);
	v->len = lenbase(v->i, 2);
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

int				binary(t_vars v, va_list ap, t_fmt *f)
{
	t_bools b;

	blength(&v, ap, f, &b);
	if ((f->width > v.len || f->prec > v.len) && !f->left)
		handle_neg(f, &v);
	ft_putstr(ft_itoa_base(v.i, 2));
	return (kill_lines(&v, f, &b));
}
