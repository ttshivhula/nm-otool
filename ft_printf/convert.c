/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 11:52:11 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/08/13 11:29:58 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Checks for the conversions that needs to be done shii like d, s you name it !
** this code fucks ! Lol not really the algo i have is very shitty but d marker
** will just have to live with it !
*/

static void		handle_neg(t_fmt *f, t_vars *v, t_bools *b)
{
	neg_line_kill(f, v, b);
	if (f->sign && !(b->n))
	{
		if (f->zero)
		{
			(!b->n) ? ft_putchar('+') : 0;
			f->sign = 0;
		}
		--v->df;
		b->s = 1;
	}
	v->df += ((f->width) ? (f->width - v->len) : f->prec - v->len);
	(f->prec || f->zero) ? ft_putnchar('0', v->df) : ft_putnchar(' ', v->df);
	if (f->sign)
	{
		(!b->n) ? ft_putchar('+') : 0;
	}
}

static void		length(t_vars *v, va_list ap, t_fmt *f, t_bools *b)
{
	if (f->z || f->l || f->ll || f->j)
		v->i = va_arg(ap, long long);
	else if (f->h)
		v->i = (short int)va_arg(ap, int);
	else if (f->hh)
		v->i = (signed char)va_arg(ap, int);
	else
		v->i = va_arg(ap, int);
	v->len = lenbase(v->i, 10);
	v->df = 0;
	b->n = 0;
	b->sp = 0;
	b->s = 0;
}

static void		wlength(t_vars *v, va_list ap, t_fmt *f, t_bools *b)
{
	(void)f;
	v->i = va_arg(ap, long);
	v->len = lenbase(v->i, 10);
	v->df = 0;
	b->n = 0;
	b->sp = 0;
	b->s = 0;
}

/*
** Norminette was fucking with me so this is just to reduce em lines ;)
*/

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
			return (((f->width) ? f->width + b->sp : f->prec + b->sp));
		else
			return ((f->width) ? f->width + b->sp : f->prec + b->sp);
	}
	return (v->len + b->sp);
}

int				handle_d(t_vars v, va_list ap, t_fmt *f)
{
	t_bools b;

	(!f->wide) ? length(&v, ap, f, &b) : wlength(&v, ap, f, &b);
	if (f->space && !f->sign && !(v.i < 0))
	{
		ft_putchar(' ');
		b.sp++;
	}
	if ((f->width > v.len || f->prec > v.len) && !f->left)
		handle_neg(f, &v, &b);
	else if (f->sign && !(v.i < 0))
	{
		b.sp = 1;
		ft_putchar('+');
	}
	ft_putstr(ft_itoa_base(v.i, 10));
	return (kill_lines(&v, f, &b));
}
