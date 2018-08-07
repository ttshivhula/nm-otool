/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wsrting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 14:45:04 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/08/13 09:23:55 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		init_s(t_vars *v, va_list ap, t_fmt *f)
{
	int l;

	l = 0;
	v->ws = (wchar_t *)va_arg(ap, int *);
	if (!v->ws)
	{
		ft_putstr("(null)");
		return (1);
	}
	if (f->prec)
		l = f->prec;
	v->len = ft_wstrlen(v->ws);
	if (l && v->len)
		v->len = (l < v->len) ? l : v->len;
	return (0);
}

int				handle_ws(t_vars v, va_list ap, t_fmt *f)
{
	if (init_s(&v, ap, f) == 1)
		return (6);
	v.df = 0;
	if ((f->width > v.len) && !f->left)
	{
		v.df = f->width - v.len;
		(f->zero) ? ft_putnchar('0', v.df) : ft_putnchar(' ', v.df);
	}
	ft_putwstr(v.ws);
	if ((f->width > v.len) && f->left)
	{
		v.df = f->width - v.len;
		ft_putnchar(' ', v.df);
	}
	if (v.df)
		return (f->width);
	return (v.len);
}

int				handle_wc(t_vars v, va_list ap, t_fmt *f)
{
	v.i = (wchar_t)va_arg(ap, wchar_t);
	v.len = ft_wlen(v.i);
	v.df = 0;
	if (((f->width > v.len || f->prec > v.len) && !f->left))
	{
		v.df = (f->width) ? f->width - v.len : f->prec - v.len;
		(f->zero) ? ft_putnchar('0', v.df) : ft_putnchar(' ', v.df);
	}
	ft_putwchar(v.i);
	if ((v.i >= 0) && (f->width > v.len && f->left))
	{
		v.df = (f->width) ? f->width - v.len : f->prec - v.len;
		ft_putnchar(' ', v.df);
	}
	if (v.df)
		return (f->width ? f->width : f->prec);
	return (v.len);
}
